#include "widget.h"
#include "ui_widget.h"
#include"inputwidget.h"
#include"tipswidget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_inputbt_clicked()
{
    inputwidget* inputw= new inputwidget(this);
    inputw->show(); hide();
}

void Widget::on_tipsbt_clicked()
{
    tipswidget* tipsw=new tipswidget(this);
    tipsw->show();hide();
}

void Widget::on_exitbt_clicked()
{
    close();
}
