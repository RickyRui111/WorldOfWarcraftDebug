#include "CaseInfo.h"

void Allcases::addACase(const QPair<QString,Caseinfo> & Case)
{
    Cases.push_back(Case);
}

Gamestate::Gamestate(int t,set<Warrior> &s,Base &rb,Base &bb,vector<City> city,QString str):ctime(t),
    rbase(rb),bbase(bb),report(str)
{
    for(auto i:s)
        samurai.emplace(i);
    for(auto i:city)
        cityline.push_back(i);
}

Caseinfo::Caseinfo(vector<Gamestate> game)
{
    for(auto i:game)
        info.push_back(i);
}

Caseinfo::Caseinfo(int m,int n,int r,int k,int t,string *ror,string *bor,map<string,int> &H,map<string,int> &at)
:M(m),N(n),R(r),K(k),T(t),hp(H),atk(at)
{
    copy(ror,ror+5,rord);
    copy(bor,bor+5,bord);
};

Caseinfo::Caseinfo(){};

void Caseinfo::addState(Gamestate g)
{
    info.push_back(g);
}

#define maxn 35
#define rep(a,b,c)	for (int (a)=b;a<=c;a++)
#define per(a,b,c)	for (int (a)=b;a>=c;a--)

using namespace std;

int t;
string rord[5]={"iceman","lion","wolf","ninja","dragon"};
string bord[5]={"lion","dragon","ninja","iceman","wolf"};
map<string,int> hp,atk,cnt;
int M,N,R,K,T;

Warrior::Warrior(string s,int ptr,int M_have,int c){
        name=s;
        id=ptr;
        color=c;
        icestep=0;
        loyalty=0;
        if (!c)  place=0,dir=1;
        else    place=N+1,dir=-1;
        weapon[0]=weapon[1]=weapon[2]=0;
        attk=atk[s];
        strength=hp[s];
        if (s=="dragon"){
            weapon[ptr%3]=1;
            morale=1.0*M_have/hp[s];
        }
        if (s=="ninja"){
            weapon[ptr%3]=weapon[(ptr+1)%3]=1;
        }
        if (s=="iceman"){
            weapon[ptr%3]=1;
        }
        if (s=="lion"){
            loyalty=M_have;
        }
        if (weapon[0])  swordatk=0.2*attk;
        else    swordatk=0;
        if (weapon[2])  arrowrem=3;
        else    arrowrem=0;
}

bool Warrior::operator < (const Warrior &b)const{
        if (place==b.place){
            if (color==b.color){
                return name<b.name;
            }
            return color<b.color;
        }
        return place<b.place;
    }

City::City(int p){
        flag=0;
        m=0;
        pos=p;
        prevwinner=0;
    }

City city[maxn];
set<Warrior> samurai;
Base::Base(int _M){
        m=_M;
        down=0;
        ptr=0;
        enemycnt=0;
}

Warrior Base::build(bool color){
        if (!color){//红色 按照红色造
            string name=rord[ptr%5];
            if (m>=hp[name]){
                m-=hp[name];
                auto person=Warrior(name,ptr+1,m,0);
                samurai.emplace(person);
                ptr++;
                return person;
            }
            return Warrior("no",0,0,0);
        }
        else{
            string name=bord[ptr%5];
            if (m>=hp[name]){
                m-=hp[name];
                auto person=Warrior(name,ptr+1,m,1);
                samurai.emplace(person);
                ptr++;
                return person;
            }
            return Warrior("no",0,0,0);
        }
}

void init(){
    rep(i,0,N+1){
        city[i]=City(i);
    }
    hp.clear();
    atk.clear();
    samurai.clear();
}

bool virtualfight(int place,Warrior wblue,Warrior wred,int col){//
    if (wred.color) swap(wred,wblue);
    Warrior mred=wred,mblue=wblue;
    bool first;//
    if ((city[place].flag==0&&place&1)||city[place].flag==1){//
        first=0;
        wblue.strength-=wred.attk+wred.swordatk;
        wred.swordatk*=0.8;
        if (wblue.strength>0){
            if (wblue.name!="ninja"){//
                wred.strength-=wblue.attk/2+wblue.swordatk;
                wblue.swordatk*=0.8;
            }
        }
    }
    if ((city[place].flag==0 && (place&1)^1)||city[place].flag==2){//
        first=1;
        wred.strength-=wblue.attk+wblue.swordatk;
        wblue.swordatk*=0.8;
        if (wred.strength>0){
            if (wred.name!="ninja"){
                wblue.strength-=wred.attk/2+wred.swordatk;
                wred.swordatk*=0.8;
            }
        }
    }
    if (wred.color==col&&wred.strength<=0){
        return 1;
    }
    if (wblue.color==col&&wblue.strength<=0){
        return 1;
    }
    return 0;
}

QString output="";
Caseinfo *ANS;

Allcases correctrun(QString data){
    QStringList lines = data.split(QRegExp("\n"), QString::SkipEmptyParts);
    vector<int> intArray;

    for (const QString &line : lines) {
        // 按空格分割每行的数字，并转换为 int
        QStringList numbers = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for (const QString &numberStr : numbers) {
            bool ok;
            int number = numberStr.toInt(&ok); // 尝试转换字符串为整数
            if (ok) {
                intArray.push_back(number); // 如果转换成功，添加到一维数组中
            } else {
                // 处理转换失败的情况（例如，打印错误消息）
                qDebug() << "无法将字符串转换为整数：" << numberStr;
            }
        }
    }

    int indexcnt=0;
    int t;
    t=intArray[indexcnt++];
    Allcases All;
    rep(i,1,t){
        //printf("Case %d:\n",i);
        //
        //以下为提前要一个值而已
        //scanf("%d",&t);
        int indexcn=indexcnt;
        vector<int>v=intArray;
        M=v[indexcn++];
        N=v[indexcn++];
        R=v[indexcn++];
        K=v[indexcn++];
        T=v[indexcn++];
        hp["dragon"]=v[indexcn++];
        //scanf("%d",&tmp);
        hp["ninja"]=v[indexcn++];
        //scanf("%d",&tmp);
        hp["iceman"]=v[indexcn++];
        //scanf("%d",&tmp);
        hp["lion"]=v[indexcn++];
        //scanf("%d",&tmp);
        hp["wolf"]=v[indexcn++];
        //scanf("%d",&tmp);
        atk["dragon"]=v[indexcn++];
        //scanf("%d",&tmp);
        atk["ninja"]=v[indexcn++];
        //scanf("%d",&tmp);
        atk["iceman"]=v[indexcn++];
        //scanf("%d",&tmp);
        atk["lion"]=v[indexcn++];
        //scanf("%d",&tmp);
        atk["wolf"]=v[indexcn++];
        output="";
        Caseinfo ans(M,N,R,K,T,rord,bord,hp,atk);
        ANS=&ans;
        output+=QString("Case %1:\n").arg(i);
        indexcnt=solve(intArray,indexcnt);
        QPair<QString,Caseinfo> tmp(output,ans);
        All.addACase(tmp);
    }
    return All;
}

void saveAState(int t,Base rb,Base bb,QString str)
{
    vector<City> cityvec;
    for(int i=1;i<=N;++i)
        cityvec.push_back(city[i]);
    ANS->addState(Gamestate(t,samurai,rb,bb,cityvec,str));
}

int solve(vector<int> v,int indexcnt){
    //scanf("%d%d%d%d%d",&M,&N,&R,&K,&T);
    M=v[indexcnt++];
    N=v[indexcnt++];
    R=v[indexcnt++];
    K=v[indexcnt++];
    T=v[indexcnt++];
    init();
    Base rbase(M),bbase(M);
    int tmp;
    //scanf("%d",&tmp);
    hp["dragon"]=v[indexcnt++];
    //scanf("%d",&tmp);
    hp["ninja"]=v[indexcnt++];
    //scanf("%d",&tmp);
    hp["iceman"]=v[indexcnt++];
    //scanf("%d",&tmp);
    hp["lion"]=v[indexcnt++];
    //scanf("%d",&tmp);
    hp["wolf"]=v[indexcnt++];
    //scanf("%d",&tmp);
    atk["dragon"]=v[indexcnt++];
    //scanf("%d",&tmp);
    atk["ninja"]=v[indexcnt++];
    //scanf("%d",&tmp);
    atk["iceman"]=v[indexcnt++];
    //scanf("%d",&tmp);
    atk["lion"]=v[indexcnt++];
    //scanf("%d",&tmp);
    atk["wolf"]=v[indexcnt++];
    for (int t=0;t<=T;t++){
        int hour=t/60;
        int minute=t-hour*60;
        switch (minute){
            case (0):{
                auto p=rbase.build(0);
                QString outpu="";
                if (p.name!="no")   outpu+=QString("%1:%2 red %3 %4 born\n")
                        .arg(hour, 3, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                        .arg(minute, 2, 10, QChar('0')) // 同样地处理分钟
                        .arg(p.name.c_str()) // 直接使用 QString
                        .arg(p.id);
                if (p.name=="dragon")   outpu += QString("Its morale is %1\n").arg(p.morale, 0, 'f', 2);
                if (p.name=="lion")   outpu+= QString("Its loyalty is %1\n").arg(p.loyalty);

                p=bbase.build(1);
                if (p.name!="no")   outpu+=QString("%1:%2 blue %3 %4 born\n")
                        .arg(hour, 3, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                        .arg(minute, 2, 10, QChar('0')) // 同样地处理分钟
                        .arg(p.name.c_str()) // 直接使用 QString
                        .arg(p.id);
                if (p.name=="dragon")   outpu += QString("Its morale is %1\n").arg(p.morale, 0, 'f', 2);//printf("Its morale is %.2lf\n",p.morale);
                if (p.name=="lion")   outpu+= QString("Its loyalty is %1\n").arg(p.loyalty);//printf("Its loyalty is %d\n",p.loyalty);
                saveAState(t,rbase,bbase,outpu);
                output+=outpu;
                break;
            }
            case (5):{
                QString outpu="";
                vector<Warrior> tobeerased;
                for (auto i:samurai){
                    if (i.name=="lion"&&i.loyalty<=0){
                        if (i.place==0&&!i.color){
                            QString colorStr = i.color ? "blue" : "red";
                            outpu+=QString("%1:%2 %3 %4 %5 ran away\n")
                                    .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(minute, 2, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(colorStr) // 条件字符串
                                    .arg(i.name.c_str()) // 将 std::string 转换为 QString
                                    .arg(i.id); // 整数
                            //printf("%.3d:%.2d %s %s %d ran away\n",hour,minute,i.color?"blue":"red",i.name.c_str(),i.id);
                            tobeerased.push_back(i);
                        }
                        if (i.place==N+1&&i.color){
                            QString colorStr = i.color ? "blue" : "red";
                            outpu+=QString("%1:%2 %3 %4 %5 ran away\n")
                                    .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(minute, 2, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(colorStr) // 条件字符串
                                    .arg(i.name.c_str()) // 将 std::string 转换为 QString
                                    .arg(i.id); // 整数
                            //printf("%.3d:%.2d %s %s %d ran away\n",hour,minute,i.color?"blue":"red",i.name.c_str(),i.id);
                            tobeerased.push_back(i);
                        }
                        if (i.place>=1&&i.place<=N){
                            QString colorStr = i.color ? "blue" : "red";
                            outpu+=QString("%1:%2 %3 %4 %5 ran away\n")
                                    .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(minute, 2, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                                    .arg(colorStr) // 条件字符串
                                    .arg(i.name.c_str()) // 将 std::string 转换为 QString
                                    .arg(i.id); // 整数
                            //printf("%.3d:%.2d %s %s %d ran away\n",hour,minute,i.color?"blue":"red",i.name.c_str(),i.id);
                            tobeerased.push_back(i);
                        }
                    }
                }
                for (auto i:tobeerased){
                    samurai.erase(i);//这里直接移除了
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
            case (10):{
                QString outpu="";
                set<Warrior> tobeerased;
                for (auto i:samurai){
                    if (!i.color&&i.place==N+1) continue;
                    if (i.color&&i.place==0)    continue;
                    auto k=i;
                    k.place+=k.dir;//修改了place
                    tobeerased.emplace(k);
                }
                for (auto k:tobeerased){
                    auto tmp=k;
                    tmp.place-=tmp.dir;//还原了place
                    samurai.erase(tmp);//删除了旧place的武士
                    if (k.name=="iceman"){
                        k.icestep++;
                        if (k.icestep&1^1){
                            k.strength-=9;
                            k.attk+=20;
                            if (k.strength<=0)  k.strength=1;
                        }
                    }
                    if (k.place==0||k.place==N+1){
                        QString colorStr = k.color ? "blue" : "red";
                        QString oppositeColorStr = k.color ? "red" : "blue";
                        outpu+= QString("%1:%2 %3 %4 %5 reached %6 with %7 elements and force %8\n")
                                .arg(hour, 3, 10, QChar('0'))
                                .arg(minute, 2, 10, QChar('0'))
                                .arg(colorStr)
                                .arg(k.name.c_str())
                                .arg(k.id)
                                .arg(oppositeColorStr)
                                .arg(k.strength)
                                .arg(k.attk);
                        //printf("%.3d:%.2d %s %s %d reached %s headquarter with %d elements and force %d\n",
                          //  hour,minute,k.color?"blue":"red",k.name.c_str(),k.id,k.color?"red":"blue",k.strength,k.attk);
                        if (k.color)    rbase.enemycnt++;
                        else    bbase.enemycnt++;
                        if (rbase.enemycnt>=2&&!rbase.down){
                            outpu+=QString("%1:%2 red headquarter was taken\n")
                                          .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                          .arg(minute, 2, 10, QChar('0')); // 2 宽度，10 基数（十进制），用 '0' 填充
                            //printf("%1:%2 red headquarter was taken\n",hour,minute);
                            rbase.down=1;
                        }
                        if (bbase.enemycnt>=2&&!bbase.down){
                            outpu+=QString("%1:%2 blue headquarter was taken\n")
                                          .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                          .arg(minute, 2, 10, QChar('0')); // 2 宽度，10 基数（十进制），用 '0' 填充
                            //printf("%.3d:%.2d blue headquarter was taken\n",hour,minute);
                            bbase.down=1;
                        }
                    }
                    else{
                        QString colorStr = k.color ? "blue" : "red";
                        outpu+= QString("%1:%2 %3 %4 %5 marched to city %6 with %7 elements and force %8\n")
                                .arg(hour, 3, 10, QChar('0'))
                                .arg(minute, 2, 10, QChar('0'))
                                .arg(colorStr)
                                .arg(k.name.c_str())
                                .arg(k.id)
                                .arg(k.place)
                                .arg(k.strength)
                                .arg(k.attk);
                        //printf("%.3d:%.2d %s %s %d marched to city %d with %d elements and force %d\n",
                            //hour,minute,k.color?"blue":"red",k.name.c_str(),k.id,k.place,k.strength,k.attk);
                    }
                    samurai.emplace(k);//新的武士放进去
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                if (rbase.down||bbase.down)    return indexcnt;//return 游戏结束
                break;
            }
            case (20):{
                rep(i,1,N){
                    city[i].m+=10;
                }
                saveAState(t,rbase,bbase,QString(""));
                break;
            }
            case (30):{
                QString outpu="";
                vector<Warrior> cnt[maxn];
                for (auto i:samurai){
                    cnt[i.place].push_back(i);
                }
                rep(i,1,N){
                    if (cnt[i].size()==1){
                        QString colorStr = cnt[i][0].color ? "blue" : "red";
                        outpu+=QString("%1:%2 %3 %4 %5 earned %6 elements for his headquarter\n")
                                .arg(hour, 3, 10, QChar('0')) // 3 宽度，10 基数（十进制），用 '0' 填充
                                .arg(minute, 2, 10, QChar('0')) // 2 宽度，10 基数（十进制），用 '0' 填充
                                .arg(colorStr) // 条件字符串
                                .arg(cnt[i][0].name.c_str()) // 将 std::string 转换为 QString
                                .arg(cnt[i][0].id) // 直接使用 int
                                .arg(city[i].m); // 直接使用 int
                        //printf("%.3d:%.2d %s %s %d earned %d elements for his headquarter\n",
                            //hour,minute,cnt[i][0].color?"blue":"red",cnt[i][0].name.c_str(),cnt[i][0].id,city[i].m);
                        if (cnt[i][0].color){
                            bbase.m+=city[i].m;
                            city[i].m=0;
                        }
                        else{
                            rbase.m+=city[i].m;
                            city[i].m=0;
                        }
                    }
                }
                saveAState(t,rbase,bbase,outpu);
                output+=outpu;
                break;
            }
            case (35):{
                QString outpu="";
                set<Warrior> tobechanged;
                for (auto i=samurai.begin();i!=samurai.end();i++){
                    if (i->arrowrem){//
                        for (auto j=samurai.begin();j!=samurai.end();j++){
                            if (j->color!=i->color&&j->place==i->place+i->dir&&i->place+i->dir!=0&&i->place+i->dir!=N+1){//
                                if (j->strength>R)
                                    outpu+= QString("%1:%2 %3 %4 %5 shot\n")
                                                                .arg(hour, 3, 10, QChar('0'))
                                                                .arg(minute, 2, 10, QChar('0'))
                                                                .arg(i->color?"blue":"red")
                                                                .arg(i->name.c_str())
                                                                .arg(i->id);
                                    //printf("%.3d:%.2d %s %s %d shot\n",hour,minute,i->color?"blue":"red",i->name.c_str(),i->id);
                                else
                                    outpu+= QString("%1:%2 %3 %4 %5 shot and killed %6 %7 %8\n")
                                                                .arg(hour, 3, 10, QChar('0'))
                                                                .arg(minute, 2, 10, QChar('0'))
                                                                .arg(i->color?"blue":"red")
                                                                .arg(i->name.c_str())
                                                                .arg(i->id)
                                                                .arg(j->color?"blue":"red")
                                                                .arg(j->name.c_str())
                                                                .arg(j->id);
                                    //printf("%.3d:%.2d %s %s %d shot and killed %s %s %d\n"
                                    //,hour,minute,i->color?"blue":"red",i->name.c_str(),i->id,j->color?"blue":"red",j->name.c_str(),j->id);
                                i->arrowrem-=1;
                                j->strength-=R;
                            }
                        }
                    }
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
            case (38):{
                QString outpu="";
                set<Warrior> tobeerased;
                for (auto i:samurai){
                    for (auto j:samurai){
                        if (i.place==j.place&&i.color!=j.color&&i.weapon[1]){//i
                            if (i.strength<=0||j.strength<=0)   continue;
                            if (tobeerased.count(i)||tobeerased.count(j))   continue;
                            Warrior wblue=i,wred=j;
                            if (wred.color) swap(wred,wblue);
                            bool use=virtualfight(i.place,wblue,wred,i.color);
                            if (use){
                                outpu+=QString("%1:%2 %3 %4 %5 used a bomb and killed %6 %7 %8\n")
                                    .arg(hour, 3, 10, QChar('0')) // 小时，2位宽度，十进制，用0填充
                                    .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                    .arg(i.color?"blue":"red") // 攻击者颜色
                                    .arg(i.name.c_str()) // 攻击者名字
                                    .arg(i.id) // 攻击者ID
                                    .arg(j.color?"blue":"red") // 目标颜色
                                    .arg(j.name.c_str()) // 目标名字
                                    .arg(j.id); // 目标ID
                                //printf("%.3d:%.2d %s %s %d used a bomb and killed %s %s %d\n",
                                    //hour,minute,i.color?"blue":"red",i.name.c_str(),i.id,j.color?"blue":"red",j.name.c_str(),j.id);
                                tobeerased.emplace(i);
                                tobeerased.emplace(j);
                            }
                        }
                    }
                }
                for (auto i:tobeerased){
                    samurai.erase(i);
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
            case (40):{
                QString outpu="";
                set<Warrior> tobeerased,tobeadded;
                set<Warrior> tobebluerewarded,toberedrewarded;
                int bluem=bbase.m,redm=rbase.m;
                for (auto i:samurai){
                    for (auto j:samurai){
                        if (i.color!=j.color&&i.place==j.place&&i.color){//
                            tobeerased.emplace(i);
                            tobeerased.emplace(j);
                            int place=i.place;
                            Warrior wred=i,wblue=j;
                            if (wred.color) swap(wred,wblue);
                            Warrior mred=wred,mblue=wblue;
                            bool first=(city[place].flag==0&&place&1^1)||city[place].flag==2;//
                            if (wred.strength<=0&&wblue.strength<=0)   continue;
                            if (wred.strength<=0&&wblue.strength>0) goto BlueSurvived;
                            if (wred.strength>0&&wblue.strength<=0) goto RedSurvived;
                            if ((city[place].flag==0&&place&1)||city[place].flag==1){//
                                first=0;
                                outpu+= QString("%1:%2 red %3 %4 attacked blue %5 %6 in city %7 with %8 elements and force %9\n")
                                    .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充（如果确实需要3位）
                                    .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                    .arg(QString::fromStdString(wred.name)) // 红色方的名字
                                    .arg(wred.id) // 红色方的ID
                                    .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                    .arg(wblue.id) // 蓝色方的ID
                                    .arg(place) // 地点
                                    .arg(wred.strength) // 红色方的兵力
                                    .arg(wred.attk); // 红色方的攻击力
                                //printf("%.3d:%.2d red %s %d attacked blue %s %d in city %d with %d elements and force %d\n",
                                  //  hour,minute,wred.name.c_str(),wred.id,wblue.name.c_str(),wblue.id,place,wred.strength,wred.attk);
                                wblue.strength-=wred.attk+wred.swordatk;
                                wred.swordatk*=0.8;
                                if (wblue.strength>0){
                                    if (wblue.name!="ninja"){//
                                        outpu+=QString("%1:%2 blue %3 %4 fought back against red %5 %6 in city %7\n")
                                                .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                                .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                                .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                                .arg(wblue.id) // 蓝色方的ID
                                                .arg(QString::fromStdString(wred.name)) // 红色方的名字
                                                .arg(wred.id) // 红色方的ID
                                                .arg(place); // 地点
                                        //printf("%.3d:%.2d blue %s %d fought back against red %s %d in city %d\n",
                                          //  hour,minute,wblue.name.c_str(),wblue.id,wred.name.c_str(),wred.id,place);
                                        wred.strength-=wblue.attk/2+wblue.swordatk;
                                        wblue.swordatk*=0.8;
                                    }
                                }
                            }
                            if ((city[place].flag==0&&place&1^1)||city[place].flag==2){//
                                first=1;
                                outpu+=QString("%1:%2 blue %3 %4 attacked red %5 %6 in city %7 with %8 elements and force %9\n")
                                        .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                        .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                        .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                        .arg(wblue.id) // 蓝色方的ID
                                        .arg(QString::fromStdString(wred.name)) // 红色方的名字
                                        .arg(wred.id) // 红色方的ID
                                        .arg(place) // 地点
                                        .arg(wblue.strength) // 蓝色方的兵力
                                        .arg(wblue.attk); // 蓝色方的攻击力
                                //printf("%.3d:%.2d blue %s %d attacked red %s %d in city %d with %d elements and force %d\n",
                                  //  hour,minute,wblue.name.c_str(),wblue.id,wred.name.c_str(),wred.id,place,wblue.strength,wblue.attk);
                                wred.strength-=wblue.attk+wblue.swordatk;
                                wblue.swordatk*=0.8;
                                if (wred.strength>0){
                                    if (wred.name!="ninja"){
                                        outpu+=QString("%1:%2 red %3 %4 fought back against blue %5 %6 in city %7\n")
                                                .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                                .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                                .arg(QString::fromStdString(wred.name)) // 红色方的名字
                                                .arg(wred.id) // 红色方的ID
                                                .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                                .arg(wblue.id) // 蓝色方的ID
                                                .arg(place); // 地点

                                        //printf("%.3d:%.2d red %s %d fought back against blue %s %d in city %d\n",
                                          //  hour,minute,wred.name.c_str(),wred.id,wblue.name.c_str(),wblue.id,place);
                                        wblue.strength-=wred.attk/2+wred.swordatk;
                                        wred.swordatk*=0.8;
                                    }
                                }
                            }
                            //
                            if (wred.strength>0&&wblue.strength<=0){//
                                outpu+=QString("%1:%2 blue %3 %4 was killed in city %5\n")
                                        .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                        .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                        .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                        .arg(wblue.id) // 蓝色方的ID
                                        .arg(place); // 地点
                                //printf("%.3d:%.2d blue %s %d was killed in city %d\n",hour,minute,wblue.name.c_str(),wblue.id,place);
                                if (wblue.name=="lion") wred.strength+=mblue.strength;//lion
                                RedSurvived:
                                if (wred.name=="wolf"){//wolf
                                    if (wred.swordatk<=0)   wred.swordatk=wblue.swordatk;//sword
                                    if (wred.arrowrem<=0)   wred.arrowrem=wblue.arrowrem;//arrow
                                    wred.weapon[1]|=wblue.weapon[1];//bomb
                                }
                                if (wred.name=="dragon")  wred.morale+=0.2;//dragon
                                if (wred.name=="dragon"&&first==0&&wred.morale>0.8){
                                    outpu+=QString("%1:%2 red dragon %3 yelled in city %4\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(wred.id) // 红色龙的ID
                                            .arg(place); // 地点
                                    //    printf("%.3d:%.2d red dragon %d yelled in city %d\n",hour,minute,wred.id,place);
                                }
                                if (city[place].m){//
                                    outpu+=QString("%1:%2 red %3 %4 earned %5 elements for his headquarter\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(QString::fromStdString(wred.name)) // 红色方的名字
                                            .arg(wred.id) // 红色方的ID
                                            .arg(city[place].m); // 特定城市的 m 属性值
                                    //printf("%.3d:%.2d red %s %d earned %d elements for his headquarter\n",
                                    //    hour,minute,wred.name.c_str(),wred.id,city[place].m);
                                    rbase.m+=city[place].m;
                                    city[place].m=0;
                                }
                                if (city[place].flag!=1&&city[place].prevwinner==1){//
                                    outpu+=QString("%1:%2 red flag raised in city %3\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(place); // 地点
                                    //printf("%.3d:%.2d red flag raised in city %d\n",hour,minute,place);
                                    city[place].flag=1;
                                }
                                city[place].prevwinner=1;
                                toberedrewarded.emplace(wred);
                                tobeadded.emplace(wred);
                            }
                            if (wred.strength<=0&&wblue.strength>0){//
                                outpu+=QString("%1:%2 red %3 %4 was killed in city %5\n")
                                        .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                        .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                        .arg(QString::fromStdString(wred.name)) // 将 std::string 转换为 QString
                                        .arg(wred.id) // 红色方的ID
                                        .arg(place); // 地点
                                //printf("%.3d:%.2d red %s %d was killed in city %d\n",hour,minute,wred.name.c_str(),wred.id,place);
                                if (wred.name=="lion")  wblue.strength+=mred.strength;//lion
                                BlueSurvived:
                                if (wblue.name=="wolf"){//
                                    if (wblue.swordatk<=0)   wblue.swordatk=wred.swordatk;//sword
                                    if (wblue.arrowrem<=0)   wblue.arrowrem=wred.arrowrem;//arrow
                                    wblue.weapon[1]|=wred.weapon[1];//bomb
                                }
                                if (wblue.name=="dragon")  wblue.morale+=0.2;//dragon
                                if (wblue.name=="dragon"&&first==1&&wblue.morale>0.8){
                                    outpu+=QString("%1:%2 blue dragon %3 yelled in city %4\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(wblue.id) // 蓝色龙的ID
                                            .arg(place); // 地点
                                    //printf("%.3d:%.2d blue dragon %d yelled in city %d\n",hour,minute,wblue.id,place);
                                }
                                if (city[place].m){//
                                    outpu+=QString("%1:%2 blue %3 %4 earned %5 elements for his headquarter\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(QString::fromStdString(wblue.name)) // 蓝色方的名字
                                            .arg(wblue.id) // 蓝色方的ID
                                            .arg(city[place].m); // 获得的元素数量
                                    //printf("%.3d:%.2d blue %s %d earned %d elements for his headquarter\n",
                                        //hour,minute,wblue.name.c_str(),wblue.id,city[place].m);
                                    bbase.m+=city[place].m;
                                    city[place].m=0;
                                }
                                if (city[place].flag!=2&&city[place].prevwinner==2){//
                                    outpu+=QString("%1:%2 blue flag raised in city %3\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(place); // 地点
                                    //printf("%.3d:%.2d blue flag raised in city %d\n",hour,minute,place);
                                    city[place].flag=2;
                                }
                                city[place].prevwinner=2;
                                tobebluerewarded.emplace(wblue);
                                tobeadded.emplace(wblue);
                            }
                            if (wred.strength>0&&wblue.strength>0){//
                                city[place].prevwinner=0;
                                if (wred.name=="dragon")    wred.morale-=0.2;
                                if (wblue.name=="dragon")    wblue.morale-=0.2;
                                if (wred.name=="dragon"&&first==0&&wred.morale>0.8){
                                    outpu+=QString("%1:%2 red dragon %3 yelled in city %4\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(wred.id) // 红色龙的ID
                                            .arg(place); // 地点
                                    //printf("%.3d:%.2d red dragon %d yelled in city %d\n",hour,minute,wred.id,place);
                                }
                                if (wblue.name=="dragon"&&first==1&&wblue.morale>0.8){
                                    outpu+=QString("%1:%2 blue dragon %3 yelled in city %4\n")
                                            .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                            .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                            .arg(wblue.id) // 蓝色龙的ID
                                            .arg(place); // 地点
                                    //printf("%.3d:%.2d blue dragon %d yelled in city %d\n",hour,minute,wblue.id,place);
                                }
                                if (wred.name=="lion")  wred.loyalty-=K;
                                if (wblue.name=="lion") wblue.loyalty-=K;
                                tobeadded.emplace(wred);
                                tobeadded.emplace(wblue);
                            }
                        }
                    }
                }
                for (auto i:tobeerased) samurai.erase(i);
                for (auto i:tobeadded) samurai.emplace(i);
                tobeerased.clear();
                for (auto i:samurai){//
                    if (i.strength<=0)  tobeerased.emplace(i);
                }
                for (auto i:tobeerased) samurai.erase(i);
                for (auto i=tobebluerewarded.begin();i!=tobebluerewarded.end();i++){
                    if (bluem>=8){
                        bluem-=8;
                        bbase.m-=8;
                        auto ptr=samurai.find(*i);
                        ptr->strength+=8;
                    }
                }
                for (auto i=toberedrewarded.rbegin();i!=toberedrewarded.rend();i++){
                    if (redm>=8){
                        redm-=8;
                        rbase.m-=8;
                        auto ptr=samurai.find(*i);
                        ptr->strength+=8;
                    }
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
            case (50):{
                QString outpu="";
                outpu+=QString("%1:%2 %3 elements in red headquarter\n")
                        .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                        .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                        .arg(rbase.m); // 红色基地的元素数量
            //printf("%.3d:%.2d %d elements in red headquarter\n",hour,minute,rbase.m);
              outpu+=QString("%1:%2 %3 elements in blue headquarter\n")
                      .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                      .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                      .arg(bbase.m); // 红色基地的元素数量
            //printf("%.3d:%.2d %d elements in blue headquarter\n",hour,minute,bbase.m);
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
            case (55):{
                QString outpu="";
                for (auto i=samurai.begin();i!=samurai.end();i++){
                    if (!i->color){
                        Warrior k=*i;
                        k.weapon[0]=k.swordatk;
                        k.weapon[2]=k.arrowrem;
                        bool first=1;
                        outpu+= QString("%1:%2 red %3 %4 has ").arg(
                                    hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                    .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                    .arg(QString::fromStdString(k.name)) // 转换为 QString 的 k.name
                                    .arg(k.id); // k 的 ID
                        //printf("%.3d:%.2d red %s %d has ",hour,minute,k.name.c_str(),k.id);
                        if (k.weapon[2]){
                            outpu+=QString("arrow(%1)").arg(k.weapon[2]);
                            //printf("arrow(%d)",k.weapon[2]);
                            first=0;
                        }
                        if (k.weapon[1]){
                            if (!first)
                                outpu+=",";
                                //printf(",");
                            outpu+="bomb";
                            //printf("bomb");
                            first=0;
                        }
                        if (k.weapon[0]){
                            if (!first)
                                outpu+=",";
                                //printf(",");
                            outpu+=QString("sword(%1)").arg(k.weapon[0]);
                            //printf("sword(%d)",k.weapon[0]);
                            first=0;
                        }
                        if (first)
                            outpu+="no weapon";
                            //printf("no weapon");
                        outpu+="\n";
                        //printf("\n");
                    }
                }
                for (auto i=samurai.begin();i!=samurai.end();i++){
                    if (i->color){
                        Warrior k=*i;
                        k.weapon[0]=k.swordatk;
                        k.weapon[2]=k.arrowrem;
                        bool first=1;
                        outpu+=QString("%1:%2 blue %3 %4 has ")
                                .arg(hour, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                                .arg(minute, 2, 10, QChar('0')) // 分钟，2位宽度，十进制，用0填充
                                .arg(QString::fromStdString(k.name)) // 将 k.name（std::string）转换为 QString
                                .arg(k.id); // k 的 ID
                        //printf("%.3d:%.2d blue %s %d has ",hour,minute,k.name.c_str(),k.id);
                        if (k.weapon[2]){
                            outpu+= QString("arrow(%1)").arg(k.weapon[2]);
                            //printf("arrow(%d)",k.weapon[2]);
                            first=0;
                        }
                        if (k.weapon[1]){
                            if (!first)
                                outpu+=",";
                            //printf(",");
                        outpu+="bomb";
                        //printf("bomb");
                            first=0;
                        }
                        if (k.weapon[0]){
                            if (!first)
                                outpu+=",";
                            //printf(",");
                        outpu+=QString("sword(%1)").arg(k.weapon[0]);
                        //printf("sword(%d)",k.weapon[0]);
                            first=0;
                        }
                        if (first)
                            outpu+="no weapon";
                        //printf("no weapon");
                    outpu+="\n";
                    //printf("\n");
                    }
                }
                output+=outpu;
                saveAState(t,rbase,bbase,outpu);
                break;
            }
        }
    }
    return indexcnt;
}
