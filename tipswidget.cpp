#include "tipswidget.h"
#include "ui_tipswidget.h"
#include <QFile>
#include <QTextBrowser>
#include <QTextStream>
#include <QDebug>
tipswidget::tipswidget(Widget* ww,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tipswidget)
{
    ui->setupUi(this);
    w=ww;
    QFile file(":/images/QTpictures/debugtips.txt"); // 替换为你的文件路径
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString text = in.readAll();

    ui->tipsBrowser->setPlainText(text); //
    file.close();
    } else {
    // 文件打开失败的处理
    qDebug() << "Failed to open file";
    }
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
