#ifndef MYCITYBUTTON_H
#define MYCITYBUTTON_H

#include "mybutton.h"
#include "incity.h"
class Mycitybutton:public Mybutton{
public:
    incity* incityp=nullptr;
    void addWarrior(const Warrior &W);
    Mycitybutton(const City &C,QWidget *parent,QString name="unset",QIcon image=QIcon(""),bool mask=0,bool music=0);
    void rewrite(const City &C);

};//构造函数先写信息类，剩下放后

#endif // MYCITYBUTTON_H
