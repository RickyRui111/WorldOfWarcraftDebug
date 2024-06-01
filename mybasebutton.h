#ifndef MYBASEBUTTON_H
#define MYBASEBUTTON_H

#include "mybutton.h"

class Mybasebutton:public Mybutton{
public:
    void addWarrior(const Warrior &W);
    Mybasebutton(const Base &B,QWidget *parent,QString name="",QIcon image=QIcon(""),bool mask=0,bool music=0);
    void rewrite(const Base &B);
};//构造函数先写信息类，剩下放后

#endif // MYBASEBUTTON_H
