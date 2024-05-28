#ifndef MYBUTTON_H
#define MYBUTTON_H

//新建一个Mybutton类
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include<QEvent>
#include <QHBoxLayout>
#include<QDebug>
#include <QTimer>
#include "CaseInfo.h"

class Mybutton:public QPushButton
{
    Q_OBJECT
public:
    explicit Mybutton(QWidget *parent=nullptr,
                      QString name="Unset",
                      QIcon image=QIcon(""),
                      bool mask=0,
                      bool music=0
                      );//这里要用ui升级方式创造按钮的话就不要加花里胡哨的构造函数

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

public:
    QWidget* xuanfu;
    QLabel *xLabel;
    QBoxLayout *layout;
    vector<QLabel*> Labels;
    vector<Mybutton*> Mybuttons;
};




#endif // MYBUTTON_H
