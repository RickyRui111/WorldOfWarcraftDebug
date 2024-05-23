#ifndef TEST_H
#define TEST_H

#include <QWidget>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QString input,int times,QWidget *parent = nullptr);
    ~test();

private:
    Ui::test *ui;
    QString caseinput;
    int Time;
};

#endif // TEST_H
