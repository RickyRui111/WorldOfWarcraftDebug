#include "tipswidget.h"
#include "ui_tipswidget.h"
tipswidget::tipswidget(Widget* ww,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tipswidget)
{
    ui->setupUi(this);
    w=ww;
}

tipswidget::~tipswidget()
{
    delete ui;
}

void tipswidget::on_tomainbt_clicked()
{
    w->show();
    delete this;
}
