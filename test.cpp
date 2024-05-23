#include "test.h"
#include "ui_test.h"

test::test(QString input,int times,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    caseinput=input;
    Time=times;
}

test::~test()
{
    delete ui;
}
