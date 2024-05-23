#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <QWidget>
#include<widget.h>
namespace Ui {
class tipswidget;
}

class tipswidget : public QWidget
{
    Q_OBJECT

public:
    explicit tipswidget(Widget* w,QWidget *parent = nullptr);
    ~tipswidget();

private slots:
    void on_tomainbt_clicked();

private:
    Ui::tipswidget *ui;
    Widget* w;
};

#endif // TIPSWIDGET_H
