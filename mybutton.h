#ifndef MYBUTTON_H
#define MYBUTTON_H

//新建一个Mybutton类
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include<QEvent>

class Mybutton:public QPushButton
{
    Q_OBJECT
public:
    explicit Mybutton(QWidget *parent=nullptr,
                      QIcon image=QIcon(""),
                      bool mask=0,
                      bool music=0,
                      int health=0,
                      int weaponn=0
                      );//这里要用ui升级方式创造按钮的话就不要加花里胡哨的构造函数

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget* xuanfu;
    QLabel *xLabel;
};




#endif // MYBUTTON_H
