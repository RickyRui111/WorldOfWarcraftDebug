#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include<widget.h>
namespace Ui {
class inputwidget;
}

class inputwidget : public QWidget
{
    Q_OBJECT

public:
    explicit inputwidget(Widget* w,QWidget *parent = nullptr);
    ~inputwidget();

private slots:
    void on_tomainbt_clicked();

    void on_confirmbt_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::inputwidget *ui;
    Widget* w;
};

#endif // INPUTWIDGET_H
