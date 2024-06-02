#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QPair>
#include "CaseInfo.h"
#include "mybutton.h"
#include "mybasebutton.h"
#include "mycitybutton.h"
#include <QTextBrowser>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    void createfromtime(int t);
    void switchtotime(int t);
    explicit test(QPair<QString,Caseinfo> &input,int times=0,int Case=1,QWidget *parent = nullptr);
    ~test();

private:
    Ui::test *ui;
    QPair<QString,Caseinfo> infopair;
    int Time;
    int Casenum;
/*    QHBoxLayout *layout;*///main

//    QVBoxLayout *Vlayout1;//sub1 放back forw
//    QVBoxLayout *Vlayout2;//sub1 放Hcities 和一个文本框

//    QHBoxLayout *Hcities;//sub2 放所有的city
//    QHBoxLayout *HWidgets;
    vector<Mycitybutton*> Mycitybuttons;
    vector<Mybasebutton*> Mybasebuttons;
    vector<QWidget*> Mywidget;
    QPushButton *back;
    QPushButton *forward;
    QLabel *reportLabel;
    QLabel *wrongcaselabel;
    QLabel *backgroundl;
    QTextBrowser *textreport;

public slots:
    void bac();
    void forw();
};


#endif // TEST_H
