#include "mybasebutton.h"

Mybasebutton::Mybasebutton(const Base &B,QWidget *parent,QString name,QIcon image,bool mask,bool music):Mybutton(parent,name,image,mask,music)
{
    QLabel *Lelements=new QLabel(QString("生命元数量：%1").arg(B.m));
    QLabel *Ldown=!B.down ? new QLabel("状态：未被占领"):new QLabel("状态：已被占领");
    QLabel *Lenemynumber=new QLabel(QString("敌人数量：%1").arg(B.enemycnt));
    Labels.push_back(Lelements);Labels.push_back(Ldown);Labels.push_back(Lenemynumber);
    layout->addWidget(Lelements);
    layout->addWidget(Ldown);
    layout->addWidget(Lenemynumber);
}

void Mybasebutton::addWarrior(const Warrior& W){
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
   //
    BWarrior->layout->addWidget(L1);
    BWarrior->layout->addWidget(l2);
    BWarrior->layout->addWidget(l3);
    Mybuttons.push_back(BWarrior);

    layout->addWidget(BWarrior);
}

void Mybasebutton::rewrite(const Base &B)
{
    Labels[0]->setText(QString("生命元数量：%1").arg(B.m));
    Labels[1]->setText(!B.down?"状态：未被占领":"状态：已被占领");
    Labels[2]->setText(QString("敌人数量：%1").arg(B.enemycnt));
}
