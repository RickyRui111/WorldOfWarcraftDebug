#include "inwarrior.h"
#include "ui_inwarrior.h"
#include "QMovie"
inwarrior::inwarrior(Warrior& w,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inwarrior)
{
    ui->setupUi(this);
    QString s= w.color?QString("blue warrior"):QString("red warrior");
    ui->label_3->setText(s);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
}

inwarrior::~inwarrior()
{
    delete ui;
}

void inwarrior::set(const Warrior & w){
    QString s;
    if(w.name=="nulwr"){
        s=QString(":/images/QTpictures/nonep.jpg");
        QPixmap pixmap0(s); // 加载图片
        pixmap0.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setScaledContents(true);
        ui->label->setPixmap(pixmap0);
    }
    else{
        s=QString(":/images/QTpictures/%1.gif").arg(w.name.c_str());
        QMovie *movie=new QMovie(s);
        ui->label->setMovie(movie);
        movie->start();
    }

    s=w.weapon[1]? QString("have bomb"):QString("NAN");
    ui->bomblabel->setText(s);

    s=w.weapon[1]? QString(":/images/QTpictures/bombp.jpg")
                 :QString(":/images/QTpictures/nonep.jpg");
    QPixmap pixmap(s); // 加载图片
    pixmap.scaled(ui->bombp->size(), Qt::KeepAspectRatio);
    ui->bombp->setScaledContents(true);
    ui->bombp->setPixmap(pixmap);

    s=w.weapon[0]? QString("have sword(%1)").arg(w.swordatk):QString("NAN");
    ui->labelsword->setText(s);

    s=w.weapon[0]? QString(":/images/QTpictures/swordp.jpg")
                 :QString(":/images/QTpictures/nonep.jpg");
    QPixmap pixmaps(s); // 加载图片
    pixmaps.scaled(ui->swordp->size(), Qt::KeepAspectRatio);
    ui->swordp->setScaledContents(true);
    ui->swordp->setPixmap(pixmaps);

    s=w.weapon[2]? QString("have arrow(%1)").arg(w.arrowrem):QString("NAN");
    ui->arrowlabel->setText(s);

    s=w.weapon[2]? QString(":/images/QTpictures/arrowp.png")//arrow是png
                 :QString(":/images/QTpictures/nonep.jpg");
    QPixmap pixmapa(s); // 加载图片
    pixmapa.scaled(ui->arrowp->size(), Qt::KeepAspectRatio);
    ui->arrowp->setScaledContents(true);
    ui->arrowp->setPixmap(pixmapa);

    ui->basicinfo->setText(QString("hp: %1           attk: %2           name: %3").arg(w.strength).arg(w.attk).arg(w.name.c_str()));
    ui->extrainfo->hide();
       if(w.name=="iceman"){ui->extrainfo->setText(QString("iceman step:    %1").arg(w.icestep));ui->extrainfo->show();}
       if(w.name=="lion"){ui->extrainfo->setText(QString("lion loyalty:     %1").arg(w.loyalty));ui->extrainfo->show();}
       if(w.name=="dragon"){ui->extrainfo->setText(QString("dragon morale:      %1").arg(w.morale));ui->extrainfo->show();}
}
