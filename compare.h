#ifndef COMPARE_H
#define COMPARE_H

#include <QWidget>
#include"widget.h"
#include"inputwidget.h"
namespace Ui {
class compare;
}

class compare : public QWidget
{
    Q_OBJECT

public:
    int minute;
    int Casenum;
    QString DATA;
    Widget* w;
    inputwidget* iw;

public:
    explicit compare(Widget* ww,inputwidget* iww,QWidget *parent = nullptr);
    void sendData(QString data);
    ~compare();

private slots:
    void on_totestbt_clicked();

    void on_confirmbt_clicked();

    void on_tomainbt_clicked();

private:
    Ui::compare *ui;
};

#endif // COMPARE_H
