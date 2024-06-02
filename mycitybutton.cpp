#include "mycitybutton.h"
#include "CaseInfo.h"
#include <QDebug>

Mycitybutton::Mycitybutton(const City &C,QWidget *parent,QString name,QIcon image,bool mask,bool music):Mybutton(parent,name,image,mask,music)
{
    //cityflag 0 white  1 red  2 blue
    qDebug()<<"Mycitybutton constructed";
    incityp=new incity(C);
    connect(this,&QPushButton::clicked,[&]{
        incityp->show();
    });
    QString flag,lastwin;
    if(!C.flag)
    {
        flag="White";
        this->setIcon(QIcon(":/images/QTpictures/Plaincity.png"));
        this->setIconSize(this->size());
    }

    else flag=C.flag==1? "Red":"Blue";

    if(C.flag==1)
    {
        this->setIcon(QIcon(":/images/QTpictures/Redcity.png"));
        this->setIconSize(this->size());
    }

    else if(C.flag==2)
    {
        this->setIcon(QIcon(":/images/QTpictures/Bluecity.png"));
        this->setIconSize(this->size());
    }

    if(!C.prevwinner) lastwin="None";
    else lastwin=C.prevwinner==1? "Redsoldier":"Blue soldier";

    QLabel *L1=new QLabel(QString("旗帜颜色：%1").arg(flag));
    QLabel *L2=new QLabel(QString("上一个赢家：%1").arg(lastwin));
    Labels.push_back(L1);Labels.push_back(L2);

    layout->addWidget(L1);
    layout->addWidget(L2);
}

void Mycitybutton::addWarrior(const Warrior& W){
    QString Wname=QString::fromStdString(W.name);
    Mybutton *BWarrior=new Mybutton(xuanfu,Wname);
    QLabel *L1=new QLabel(QString("英雄名称：%1").arg(Wname));
    QLabel *l2=new QLabel(QString("英雄生命值：%1").arg(W.strength));
    QLabel *l3=new QLabel(QString("英雄攻击力：%1").arg(W.attk));

   //
   //
   //
   //
   //
   //
    BWarrior->layout->addWidget(L1);
    BWarrior->layout->addWidget(l2);
    BWarrior->layout->addWidget(l3);

    layout->addWidget(BWarrior);
}

void Mycitybutton::rewrite(const City &C)
{
    QString flag,lastwin;
    incityp->set(C);
    if(!C.flag)
    {
        flag="White";
        this->setIcon(QIcon(":/images/QTpictures/Plaincity.png"));
        this->setIconSize(this->size());
    }
    else flag=C.flag==1? "Red":"Blue";

    if(C.flag==1)
    {
        this->setIcon(QIcon(":/images/QTpictures/Redcity.png"));
        this->setIconSize(this->size());
    }

    else if(C.flag==2)
    {
        this->setIcon(QIcon(":/images/QTpictures/Bluecity.png"));
        this->setIconSize(this->size());
    }

    if(!C.prevwinner) lastwin="None";
    else lastwin=C.prevwinner==1? "Redsoldier":"Blue soldier";
    Labels[0]->setText(QString("旗帜颜色：%1").arg(flag));
    Labels[1]->setText(QString("上一个赢家：%1").arg(lastwin));
}
