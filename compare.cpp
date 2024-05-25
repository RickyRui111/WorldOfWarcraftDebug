#include "compare.h"
#include "ui_compare.h"
#include"test.h"
#include"correctexe.cpp"
compare::compare(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::compare)
{
    ui->setupUi(this);
    ui->totestbt->hide();
}

compare::~compare()
{
    delete ui;
}

void compare::sendData(QString data){
    DATA=data;
    ui->correctext->setText(correctrun(data));
    ui->correctext->setReadOnly(true);
}
void compare::on_totestbt_clicked()
{
    test* world = new test(DATA,Time);//wrongtext按了confirm之后别改
    world->show();
}

void compare::on_confirmbt_clicked()
{
    QString inputstr = ui->wrongtext->toPlainText();
    //文本对比
    Time=1;//Time=return of diffchecker, a time
    ui->totestbt->show();
}
