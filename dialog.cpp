#include "dialog.h"
#include "./ui_dialog.h"
#include<QPlainTextEdit>
#include<QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->confirmbt,&QPushButton::clicked,this,&Dialog::compareText);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::compareText(){
    QFile wrongTextFile("wrongTextFile.txt");
    QFile correctTextFile("correctTextFile.txt");
    if(!wrongTextFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
    }
    if(!correctTextFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
    }

    QString wstr=ui->wrongtext->toPlainText();
    QString cstr=ui->correctext->toPlainText();
    qDebug()<<wstr;
    qDebug()<<cstr;
    QTextStream cstream(&correctTextFile);
    QTextStream wstream(&wrongTextFile);
    cstream<<cstr;
    wstream<<wstr;
    //QMessageBox::warning(this,tr("Good Luck"),tr("Save File Successfully"));
    correctTextFile.close();
    wrongTextFile.close();

    if(!wrongTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
    }
    if(!correctTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
    }

    QString wlinestr,clinestr;//每次读取一行比较
    ui->wrongtext->clear();
    ui->correctext->clear();
    ui->wrongtext->setTextColor("black");
    ui->correctext->setTextColor("black");
    int wlines=0,clines=0,diflines=0;
    while((!wstream.atEnd())&&(!cstream.atEnd())){
        wlinestr=wstream.readLine();
        clinestr=cstream.readLine();
        ++wlines;++clines;
        if(wlinestr!=clinestr){
            ++diflines;
            ui->wrongtext->setTextColor("blue");
            ui->correctext->setTextColor("purple");
            ui->wrongtext->append(wlinestr);
            ui->correctext->append(clinestr);
            ui->wrongtext->setTextColor("black");
            ui->correctext->setTextColor("black");
        }
        else{
            ui->wrongtext->append(wlinestr);
            ui->correctext->append(clinestr);
        }
    }
    if(wstream.atEnd()){
        ++clines;++diflines;
        clinestr=cstream.readLine();
        ui->correctext->setTextColor("purple");
        ui->correctext->append(clinestr);
    }
    else if(cstream.atEnd()){
        ++wlines;++diflines;
        wlinestr=wstream.readLine();
        ui->wrongtext->setTextColor("blue");
        ui->wrongtext->append(wlinestr);
    }
    ui->wTextLines->setNum(wlines);
    ui->cTextLines->setNum(clines-1);//行末会自动加个'\n'符号,导致最后多出来一行,不知道怎么回事
    ui->difLines->setNum(diflines-1);//同上
    correctTextFile.close();
    wrongTextFile.close();
}

// #include "dialog.h"
// #include "./ui_dialog.h"
// #include<QPlainTextEdit>
// #include<QFileDialog>
// #include<QMessageBox>
// #include<QString>
// #include<QDebug>
// Dialog::Dialog(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::Dialog)
// {
//     ui->setupUi(this);

//     connect(ui->confirmbt,&QPushButton::clicked,this,&Dialog::compareText);
// }

// Dialog::~Dialog()
// {
//     delete ui;
// }

// void Dialog::compareText(){

//     QFile wrongTextFile("wrongTextFile.txt");
//     QFile correctTextFile("correctTextFile.txt");
//     if(!wrongTextFile.open(QIODevice::WriteOnly|QIODevice::Text)){
//         QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
//     }
//     if(!correctTextFile.open(QIODevice::WriteOnly|QIODevice::Text)){
//         QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
//     }

//     QString wstr=ui->wrongtext->toPlainText();
//     QString cstr=ui->correctext->toPlainText();
//     qDebug()<<wstr;
//     qDebug()<<cstr;
//     QTextStream cstream(&correctTextFile);
//     QTextStream wstream(&wrongTextFile);
//     cstream<<cstr;
//     wstream<<wstr;
//     //QMessageBox::warning(this,tr("Good Luck"),tr("Save File Successfully"));
//     correctTextFile.close();
//     wrongTextFile.close();

//     if(!wrongTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
//         QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
//     }
//     if(!correctTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
//         QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
//     }

//     QString wlinestr,clinestr;//每次读取一行比较
//     ui->wlistWidget->clear();
//     ui->clistWidget->clear();
//     int wlines=0,clines=0,diflines=0;
//     while((!wstream.atEnd())&&(!cstream.atEnd())){
//         wlinestr=wstream.readLine();
//         clinestr=cstream.readLine();
//         QListWidgetItem* witem=new QListWidgetItem(wlinestr);
//         QListWidgetItem* citem=new QListWidgetItem(clinestr);
//         ++wlines;++clines;
//         if(wlinestr!=clinestr){
//             ++diflines;
//             witem->setTextColor("blue");
//             citem->setTextColor("purple");
//         }
//         ui->wlistWidget->addItem(witem);
//         ui->clistWidget->addItem(citem);
//     }
//     if(wstream.atEnd()){
//         ++clines;++diflines;
//         clinestr=cstream.readLine();
//         QListWidgetItem* citem=new QListWidgetItem(clinestr);
//         citem->setTextColor("purple");
//         ui->clistWidget->addItem(citem);
//     }
//     else if(cstream.atEnd()){
//         ++wlines;++diflines;
//         wlinestr=wstream.readLine();
//         QListWidgetItem* witem=new QListWidgetItem(wlinestr);
//         witem->setTextColor("blue");
//         ui->wlistWidget->addItem(witem);
//     }
//     ui->wTextLines->setNum(wlines);
//     ui->cTextLines->setNum(clines-1);//行末会自动加个'\n'符号,导致最后多出来一行,不知道怎么回事
//     ui->difLines->setNum(diflines-1);//同上
//     correctTextFile.close();
//     wrongTextFile.close();
// }
