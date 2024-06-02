#include "incity.h"
#include "ui_incity.h"
#include"QDebug"

#include"QMessageBox"
incity::incity(const City &c,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::incity)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    set(c);
    Warrior nulw("nulwr",0,0,0);
    bw=new inwarrior(nulw);
    rw=new inwarrior(nulw);
}
void incity::set(const City& c){
    ui->label_7->setText(QString("city %1").arg(c.pos));
    ui->label_2->setText(QString("element：%1").arg(c.m));
    QString s;
    if(c.flag==2){
        s=QString("flag：blue");
        QPixmap pixmap(":/images/QTpictures/bluecityp.jpg"); // 加载图片

        pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setScaledContents(true);
        QPixmap pixmap1(":/images/QTpictures/blueflagp.jpg"); // 加载图片

        pixmap1.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label_5->setScaledContents(true);
        ui->label->setPixmap(pixmap); // 设置QLabel的Pixmap
        ui->label_5->setPixmap(pixmap1);
    }
    else if(c.flag==1){
        s=QString("flag：red");
        QPixmap pixmap(":/images/QTpictures/redcityp.jpg"); // 加载图片        
        pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setScaledContents(true);
        QPixmap pixmap1(":/images/QTpictures/redflagp.jpg"); // 加载图片        
        pixmap1.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label_5->setScaledContents(true);
        ui->label->setPixmap(pixmap); // 设置QLabel的Pixmap
        ui->label_5->setPixmap(pixmap1);
    }
    else if(c.flag==0){
        s=QString("flag:none");
        QPixmap pixmap(":/images/QTpictures/Plaincity.png"); // 加载图片
        //1.png
        //2.jpg
        pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setScaledContents(true);
        QPixmap pixmap1(":/images/QTpictures/nonep.jpg"); // 加载图片
        pixmap1.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label_5->setScaledContents(true);
        ui->label->setPixmap(pixmap); // 设置QLabel的Pixmap
        ui->label_5->setPixmap(pixmap1);
    }
    ui->label_3->setText(s);
    if(c.prevwinner==2)s=QString("lastwinner：blue");
       else if(c.prevwinner==1)s=QString("lastwinner：red");
       else if(!c.prevwinner)s=QString("lastwinner：none");
    ui->label_4->setText(s);
}

void incity::setw(const Warrior& w){
    if(w.name=="nulwr"){
        if(w.color){
            bhavew=0;
            bw->set(w);
            ui->bluewlabel->setText(QString("blue:none"));
            QString s=QString(":/images/QTpictures/nonep.jpg");
            QIcon icon(s);
            QPixmap pixmap = icon.pixmap(80, 80); // 设置你想要的图标大小
            ui->bpushButton->setIcon(QIcon(pixmap));
            ui->bpushButton->setIconSize(pixmap.size()); // 确保图标大小与pixmap相同
        }
        else{
            rhavew=0;
            rw->set(w);
            ui->redwlabel->setText(QString("red:none"));
            QString s=QString(":/images/QTpictures/nonep.jpg");
            QIcon icon(s);
            QPixmap pixmap = icon.pixmap(80, 80); // 设置你想要的图标大小
            ui->rpushButton->setIcon(QIcon(pixmap));
            ui->rpushButton->setIconSize(pixmap.size()); // 确保图标大小与pixmap相同
        }
    }
    else{
        if(w.color){
            bhavew=1;
            bw->set(w);
            ui->bluewlabel->setText(QString("blue %1 %2").arg(w.name.c_str()).arg(w.id));
            QString s=QString(":/images/QTpictures/%1.gif").arg(w.name.c_str());
            QIcon icon(s);
            QPixmap pixmap = icon.pixmap(80, 80); // 设置你想要的图标大小
            ui->bpushButton->setIcon(QIcon(pixmap));
            ui->bpushButton->setIconSize(pixmap.size()); // 确保图标大小与pixmap相同
        }
        else{
            rhavew=1;
            rw->set(w);
            ui->redwlabel->setText(QString("red %1 %2").arg(w.name.c_str()).arg(w.id));
            QString s=QString(":/images/QTpictures/%1.gif").arg(w.name.c_str());
            QIcon icon(s);
            QPixmap pixmap = icon.pixmap(80, 80); // 设置你想要的图标大小
            ui->rpushButton->setIcon(QIcon(pixmap));
            ui->rpushButton->setIconSize(pixmap.size()); // 确保图标大小与pixmap相同
        }
    }
}
incity::~incity()
{
    delete ui;
}

void incity::on_rpushButton_clicked()
{
    if(rhavew){
        rw->show();
    }
    else{
        QMessageBox::warning(this, "提示","无红武士");
    }
}

void incity::on_bpushButton_clicked()
{
    if(bhavew){
        bw->show();
    }
    else{
        QMessageBox::warning(this, "提示","无蓝武士");
    }
}
