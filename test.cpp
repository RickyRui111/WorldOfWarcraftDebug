#include "test.h"
#include "ui_test.h"
#include"incity.h"
#include"inwarrior.h"
std::map<int,int> minutetocnt={{0,0},{5,1},{10,2},{20,3},{30,4},{35,5},{38,6},{40,7},{50,8},{55,9}};
test::test(QPair<QString,Caseinfo> &input,int times,int casenum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test),layout(new QHBoxLayout),back(new QPushButton("back",this)),forward(new QPushButton("forward",this))
  ,Vlayout1(new QVBoxLayout),Vlayout2(new QVBoxLayout)
{
    ui->setupUi(this);
    infopair=input;
    Time=times;
    Casenum=casenum;
    createfromtime(Time);
    setLayout(layout);
//    this->showFullScreen();
    connect(back,&QPushButton::clicked,this,&test::bac);
    connect(forward,&QPushButton::clicked,this,&test::forw);
    Vlayout1->addWidget(back);
    Vlayout1->addWidget(forward);
    layout->addLayout(Vlayout1);
}

test::~test()
{
    delete ui;
}

void deleteLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        } else if (item->layout()) {
            deleteLayout(item->layout());
        }
        delete item;
    }
    delete layout;  // 删除布局本身
}

void printLayoutProperties(QHBoxLayout *layout) {
    if (!layout) return;  // Ensure the layout is not null

    // 获取并打印间隔和边距
    qDebug() << "Spacing:" << layout->spacing();
    qDebug() << "Contents Margins:" << layout->contentsMargins();

    // 打印布局中的项目数
    qDebug() << "Number of items in the layout:" << layout->count();

    // 遍历布局中的所有项，打印每个项的类型和可能的额外信息
    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem* item = layout->itemAt(i);
        if (item->widget()) {
            qDebug() << "Item" << i << ": Widget" << item->widget()->metaObject()->className();
        } else if (item->spacerItem()) {
            qDebug() << "Item" << i << ": SpacerItem" << item->spacerItem()->sizeHint();
        } else if (item->layout()) {
            qDebug() << "Item" << i << ": Sub-layout" << item->layout()->metaObject()->className();
        }
    }

     //如果需要，可以递归打印子布局的属性
}

void test::forw()
{
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
    emit switchtime(t);
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
}

void test::createfromtime(int t)
{
    //注意，这里的t必须要转换成对应的连续正整数索引
    //实现方式：通过文本对比中第一个错误的点的文本输出时间计算到总时间
    //         再通过一个映射映射到连续索引
    //deleteLayout(layout);
    int citysum=infopair.second.N;
    qDebug()<<citysum;
    Gamestate Ninfo=infopair.second.info[t];
    Mybasebutton *b1=new Mybasebutton(Ninfo.rbase,this,"Red");
    b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b1->setMaximumHeight(250);
//    b1->resize(165,165);//必须先setheight再resize
    Mybasebuttons.push_back(b1);
    layout->addWidget(b1);
    for(int i=1;i<=citysum;++i)
    {
        Mycitybutton *c=new Mycitybutton(Ninfo.cityline[i-1],this,QString("City%1").arg(i));
        c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        c->setMaximumHeight(200);
        //c->resize(120,120);
        layout->addWidget(c);
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
    Mybasebutton *b2=new Mybasebutton(Ninfo.bbase,this,"Blue");
    b2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b2->setMaximumHeight(250);
    //b2->resize(165,165);
    Mybasebuttons.push_back(b2);
    layout->addWidget(b2);
    printLayoutProperties(layout);
    this->adjustSize();
}
