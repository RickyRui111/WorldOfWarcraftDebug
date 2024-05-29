#include "inputwidget.h"
#include "ui_inputwidget.h"
#include"QTextDocument"
#include"compare.h"
inputwidget::inputwidget(Widget* ww,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputwidget)
{
    ui->setupUi(this);
    w=ww;
}

inputwidget::~inputwidget()
{
    delete ui;
}

void inputwidget::on_tomainbt_clicked()
{
    w->show();
    delete this;
}

void inputwidget::on_confirmbt_clicked()
{
    QString inputstr=ui->inputtextEdit->toPlainText();
    compare* compw=new compare;
    compw->sendData(inputstr);
    compw->show();

}
