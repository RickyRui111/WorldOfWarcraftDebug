#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QPair>
#include "CaseInfo.h"
#include "mybutton.h"
#include "mybasebutton.h"
#include "mycitybutton.h"
namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    void createfromtime(int t);
    void switchtotime(int t);
    explicit test(QPair<QString,Caseinfo> &input,int times=0,QWidget *parent = nullptr);
    ~test();

private:
    Ui::test *ui;
    QPair<QString,Caseinfo> infopair;
    int Time;
    QHBoxLayout *layout;//main
    QVBoxLayout *Vlayout1;
    QVBoxLayout *Vlayout2;
    vector<Mycitybutton*> Mycitybuttons;
    vector<Mybasebutton*> Mybasebuttons;
    QPushButton *back;
    QPushButton *forward;

public slots:
    void bac();
    void forw();
};


#endif // TEST_H
