#include "test.h"
#include "ui_test.h"
#include "incity.h"
#include "inwarrior.h"
#include <QScreen>
#include <QApplication>
#include <QEvent>

std::map<int,int> minutetocnt={{0,0},{5,1},{10,2},{20,3},{30,4},{35,5},{38,6},{40,7},{50,8},{55,9}};

void adjustFontSize(QLabel *label) {
    QFont font = label->font();
    int fontSize = 1;
    QFontMetrics fm(font);
    int maxWidth = label->width() - 2; // Subtract some padding
    int textWidth = fm.width(label->text());

    // Increase font size while it fits to the label width
    while (textWidth <= maxWidth && fontSize < 256) {
        font.setPointSize(fontSize);
        label->setFont(font);
        fm = QFontMetrics(font);
        textWidth = fm.width(label->text());
        fontSize++;
    }
    // Decrease font size to make sure it really fits
    if (textWidth > maxWidth) {
        font.setPointSize(fontSize - 2);
        label->setFont(font);
    }
}

void adjustFontSize(QPushButton *label) {
    QFont font = label->font();
    int fontSize = 1;
    QFontMetrics fm(font);
    int maxWidth = label->width() - 2; // Subtract some padding
    int textWidth = fm.width(label->text());

    // Increase font size while it fits to the label width
    while (textWidth <= maxWidth && fontSize < 256) {
        font.setPointSize(fontSize);
        label->setFont(font);
        fm = QFontMetrics(font);
        textWidth = fm.width(label->text());
        fontSize++;
    }
    // Decrease font size to make sure it really fits
    if (textWidth > maxWidth) {
        font.setPointSize(fontSize - 2);
        label->setFont(font);
    }
}

test::test(QPair<QString,Caseinfo> &input,int times,int Case,QWidget *parent) :
    QWidget(parent),reportLabel(new QLabel(this)),Casenum(Case),wrongcaselabel(new QLabel(this)),
    ui(new Ui::test),/*layout(new QHBoxLayout),*/back(new QPushButton("back",this)),forward(new QPushButton("forward",this))
//  ,Vlayout1(new QVBoxLayout),Vlayout2(new QVBoxLayout),Hcities(new QHBoxLayout),HWidgets(new QHBoxLayout)
    ,backgroundl(new QLabel(this)),textreport(new QTextBrowser(this))
{
    ui->setupUi(this);
    //移到屏幕中央：
//    QScreen *screen = QApplication::primaryScreen();
//    QRect screenGeometry = screen->geometry();
    this->resize(1000,650);
////    this->setFixedSize(800,650);
//    int x = (screenGeometry.width() - this->width()) / 2;
//    int y = (screenGeometry.height() - this->height()) / 2;
//    this->move(x,y);
    this->setStyleSheet("background-color: transparent;");
//"QWidget { background-image: url('/path/to/image.jpg'); }"
    backgroundl->resize(this->size());
    backgroundl ->setPixmap(QPixmap(":/images/QTpictures/Background.jpg"));
    backgroundl ->setScaledContents(true);
    backgroundl->lower();

    infopair=input;
    Time=(times/60)*10+minutetocnt[times%60];
    createfromtime(Time);
//    setLayout(layout);
    connect(back,&QPushButton::clicked,this,&test::bac);
    connect(forward,&QPushButton::clicked,this,&test::forw);
    back->move(400,425);
    forward->move(500,425);

    textreport->move(800,60);
    textreport->resize(200,240);
    QFont font2("Arial Black",8);
    textreport->setFont(font2);

    back->resize(70,50);
    forward->resize(70,50);
    back->setStyleSheet("QPushButton { border-image: url(':/images/QTpictures/white.png'); }");
    forward->setStyleSheet("QPushButton { border-image: url(':/images/QTpictures/white.png'); }");
//    adjustFontSize(back);
//    adjustFontSize(forward);
    QFont font("Agency FB",16,QFont::Bold);
    back->setFont(font);
    forward->setFont(font);
    reportLabel->resize(500,150);
    reportLabel->move((this->width()-reportLabel->width())*0.5
                      ,50);
    reportLabel->setText(QString("%1:%2")
                         .arg(infopair.second.info[Time].ctime/60, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                         .arg(infopair.second.info[Time].ctime%60, 2, 10, QChar('0'))); // 分钟，2位宽度，十进制，用0填充;
    adjustFontSize(reportLabel);

    wrongcaselabel->move(800,10);
    wrongcaselabel->resize(200,50);
    wrongcaselabel->setText(QString("Wrong Case%1").arg(Case));
    adjustFontSize(wrongcaselabel);

//    Vlayout1->addWidget(back);
//    Vlayout1->addWidget(forward);
//    Vlayout2->addLayout(Hcities);
//    Vlayout2->addLayout(HWidgets);
//    layout->addLayout(Vlayout1);
//    layout->addLayout(Vlayout2);
}

test::~test()
{
    delete ui;
//    delete layout;
    for(auto w:Mybasebuttons)
        delete w;
    for(auto w:Mycitybuttons)
        delete w;
    for(auto w:Mywidget)
        delete w;
}

void test::forw()
{
    if(Time+1!=infopair.second.info.size())
        ++Time;
    switchtotime(Time);
}


void test::bac()
{
    if(Time)
        --Time;
    switchtotime(Time);
}

void test::switchtotime(int t)//把t的世界加载出来
{
    //注意，这里的t必须要转换成对应的连续正整数索引
    //实现方式：通过文本对比中第一个错误的点的文本输出时间计算到总时间
    //         再通过一个映射映射到连续索引
    //deleteLayout(layout);
    int citysum=infopair.second.N;
    Gamestate Ninfo=infopair.second.info[t];
    qDebug()<<Ninfo.bbase.m;
    Mybasebuttons[0]->rewrite(Ninfo.rbase);
    Mybasebuttons[1]->rewrite(Ninfo.bbase);
    for(int i=1;i<=citysum;++i)
    {
        bool blueset=0,redset=0;
        Mycitybuttons[i-1]->rewrite(Ninfo.cityline[i-1]);
        for(Warrior w:Ninfo.samurai){
            if(w.place==i){
                if(w.color){
                    blueset=1;Mycitybuttons[i-1]->incityp->bhavew=1;
                    Mycitybuttons[i-1]->incityp->setw(w);
                }
                else{
                    redset=1;Mycitybuttons[i-1]->incityp->rhavew=1;
                    Mycitybuttons[i-1]->incityp->setw(w);
                }
            }
        }
        if(!blueset){Mycitybuttons[i-1]->incityp->bhavew=0;Warrior nulw("nulwr",0,0,1);
        Mycitybuttons[i-1]->incityp->setw(nulw);}
        if(!redset){Mycitybuttons[i-1]->incityp->rhavew=0;Warrior nulw("nulwr",0,0,0);
        Mycitybuttons[i-1]->incityp->setw(nulw);}
    }
    reportLabel->setText(QString("%1:%2")
                         .arg(infopair.second.info[Time].ctime/60, 3, 10, QChar('0')) // 小时，3位宽度，十进制，用0填充
                         .arg(infopair.second.info[Time].ctime%60, 2, 10, QChar('0'))); // 分钟，2位宽度，十进制，用0填充;
    adjustFontSize(reportLabel);
    QString rr=Ninfo.report;
    if(rr==QString(""))
        rr=QString("No output at this time");
    textreport->setPlainText(rr);
}

void test::createfromtime(int t)
{
    //注意，这里的t必须要转换成对应的连续正整数索引
    //实现方式：通过文本对比中第一个错误的点的文本输出时间计算到总时间
    //         再通过一个映射映射到连续索引
    //deleteLayout(layout);
    //    QLabel *citynum=new QLabel("citynum",this);
    //    Mywidget.push_back(citynum);
    //    HWidgets->addWidget(citynum);

    int basel=130;    int cityl=80;     int interval=5;//限制的最小可以接受的interval
    int citysum=infopair.second.N;
    qDebug()<<citysum;
    Gamestate Ninfo=infopair.second.info[t];
    Mybasebutton *b1=new Mybasebutton(Ninfo.rbase,this);
    b1->resize(basel,basel);
    b1->setIcon(QIcon(":/images/QTpictures/Redbase.png"));
    b1->setIconSize(b1->size());
    b1->move(0,(this->height()-b1->height())*0.5);
//    b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    b1->setMaximumHeight(250);
//    b1->resize(165,165);//必须先setheight再resize
    Mybasebuttons.push_back(b1);
//    layout->addWidget(b1);
    Mybasebutton *b2=new Mybasebutton(Ninfo.bbase,this);
    b2->resize(130,130);
    b2->setIcon(QIcon(":/images/QTpictures/Bluebase.png"));
    b2->setIconSize(b1->size());
    b2->move((this->width()-b2->width()),(this->height()-b2->height())*0.5);

    int layout=0;//0 一种方案   1 一种方案
    if(citysum*(cityl+interval)+interval<this->width()-2*basel)
        layout=1;
    /*

*/
    for(int i=1;i<=citysum;++i)
    {
        Mycitybutton *c=new Mycitybutton(Ninfo.cityline[i-1],this,QString("")/*.arg(i)*/);
        c->resize(cityl,cityl);
        c->setIconSize(c->size());
//        c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        c->setMaximumHeight(200);
        //c->resize(120,120);
//        Hcities->addWidget(c);
        if(layout==1)
        {
            int my=(this->height()-cityl)*0.5;//排在画面中央
            int ninterval=(this->width()-2*basel-citysum*cityl)/(citysum+1);
            c->move(basel+ninterval+(ninterval+cityl)*(i-1)
                                         ,my+(i%2==0?-10:10));
        }
        else
        {
            int space=this->width()-2*basel;
            int ncityl=(space-(citysum+1)*interval)/citysum;
            c->resize(ncityl,ncityl);
            c->setIconSize(c->size());
            int my=(this->height()-ncityl)*0.5;//排在画面中央
            int ninterval=(space-ncityl*citysum)/(citysum+1);
            c->move(basel+ninterval+(ninterval+ncityl)*(i-1),
                    my+(i%2==0?-10:10));
        }

        Mycitybuttons.push_back(c);
        bool blueset=0,redset=0;
        for(Warrior w:Ninfo.samurai){
            if(w.place==i){
            if(w.color){
                blueset=1;c->incityp->bhavew=1;
                c->incityp->setw(w);
            }
            else{
                redset=1;c->incityp->rhavew=1;
                c->incityp->setw(w);
            }
            }
        }

        if(!blueset){c->incityp->bhavew=0;Warrior nulw("nulwr",0,0,1);c->incityp->setw(nulw);}
        if(!redset){c->incityp->rhavew=0;Warrior nulw("nulwr",0,0,0);c->incityp->setw(nulw);}
    }
    //下面开始排city的队：

    //在最小interval限定下满足不超过
    //那就横着一条直线

//    b2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    b2->setMaximumHeight(250);
    //b2->resize(165,165);
    Mybasebuttons.push_back(b2);
//    layout->addWidget(b2);
//    //printLayoutProperties(layout);
//    this->adjustSize();
    QString rr=Ninfo.report;
    if(rr==QString(""))
        rr=QString("No output at this time");
    textreport->setPlainText(rr);
}


