#include "compare.h"
#include "ui_compare.h"
#include "test.h"
#include "CaseInfo.h"
#include <QFile>
#include <QMessageBox>
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
    output=correctrun(data);//这是一个Allcases类型 里面包含vector <QPair<QString,Caseinfo> >
    //把output改成了一个成员变量
    QString text="";
    for(auto i:output.Cases)
        text+=i.first;
    ui->correctext->setText(text);
    ui->correctext->setReadOnly(true);
}

void compare::on_totestbt_clicked()
{
    qDebug()<<"after CREATING test:  casenum:"<<Casenum;
    if(Casenum<=0)  Casenum=1;
    test* world = new test(output.Cases[Casenum-1],Time,Casenum);//wrongtext按了confirm之后别改
    //这里把那个pair传到下一个test里面
    world->show();
}

void compare::on_confirmbt_clicked()
{
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
            // qDebug()<<wstr;
            // qDebug()<<cstr;
            QTextStream cstream(&correctTextFile);
            QTextStream wstream(&wrongTextFile);
            cstream<<cstr;
            wstream<<wstr;
            correctTextFile.close();
            wrongTextFile.close();

            if(!wrongTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
                QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
            }
            if(!correctTextFile.open(QIODevice::ReadOnly|QIODevice::Text)){
                QMessageBox::warning(this,tr("Warning"),tr("Open Error!"),QMessageBox::Abort);
            }

            QString wlinestr,clinestr,caseline;//每次读取一行比较
            QString firstDifLine="";//第一次出现不同的一行
            QString lastLine="";
            QTextStream ccstream(&correctTextFile);
            QTextStream wwstream(&wrongTextFile);
            ui->wrongtext->clear();
            ui->correctext->clear();
            ui->wrongtext->setTextColor("black");
            ui->correctext->setTextColor("black");
            int wlines=0,clines=0,diflines=0;
            int casenum=-1,hours=-1,minutes=-1;
            while((!wwstream.atEnd())&&(!ccstream.atEnd())){
                wlinestr=wwstream.readLine();
                clinestr=ccstream.readLine();
                if(clinestr[0]=='C'){
                    caseline=clinestr;
                    lastLine="";
                    if(wlinestr!=clinestr){
                        ++diflines;
                        ui->wrongtext->setTextColor("red");
                        ui->correctext->setTextColor("blue");
                        ui->wrongtext->append(wlinestr);
                        ui->correctext->append(clinestr);
                        ui->wrongtext->setTextColor("black");
                        ui->correctext->setTextColor("black");
                        continue;
                    }
                    ui->wrongtext->append(wlinestr);
                    ui->correctext->append(clinestr);
                    continue;
                }
                ++wlines;++clines;
                if(wlinestr!=clinestr){
                    if(firstDifLine==""){
                        if(lastLine==""){
                            firstDifLine="000:00 ";
                        }
                        else {
                            firstDifLine=lastLine;
                        }
                    }
                    if(casenum==-1){
                        QString tmp=caseline;
                        // tmp.chop(tmp.size()-tmp.lastIndexOf(":"));
                        tmp.remove(0,5);
                        tmp.chop(1);
                        casenum=tmp.toInt();
                    }
                    ++diflines;
                    ui->wrongtext->setTextColor("red");
                    ui->correctext->setTextColor("blue");
                    ui->wrongtext->append(wlinestr);
                    ui->correctext->append(clinestr);
                    ui->wrongtext->setTextColor("black");
                    ui->correctext->setTextColor("black");
                }
                else{
                    lastLine=clinestr;
                    ui->wrongtext->append(wlinestr);
                    ui->correctext->append(clinestr);
                }
            }
            if(ccstream.atEnd()){
                while(!wwstream.atEnd()){
                    ++wlines;++diflines;
                    wlinestr=wwstream.readLine();
                    ui->wrongtext->setTextColor("red");
                    ui->wrongtext->append(wlinestr);
                }
            }
            else {
                while(!ccstream.atEnd()){
                    ++clines;++diflines;
                    clinestr=ccstream.readLine();
                    ui->correctext->setTextColor("blue");
                    ui->correctext->append(clinestr);
                    ui->wrongtext->setTextColor("red");
                }
                if(wlinestr!="(more lines needed)"){
                    ui->wrongtext->append("(more lines needed)");
                }
            }
/*            ui->wTextLines->setNum(wlines);
            ui->cTextLines->setNum(clines);//行末会自动加个'\n'符号,导致最后多出来一行,不知道怎么回事
            ui->difLines->setNum(diflines);*///加上while循环后似乎解决了
            correctTextFile.close();
            wrongTextFile.close();

            if(firstDifLine==""){
                firstDifLine=lastLine;
            }
            if(casenum==-1){
                QString tmp=caseline;
                // tmp.chop(tmp.size()-tmp.lastIndexOf(":"));
                tmp.remove(0,5);
                tmp.chop(1);
                casenum=tmp.toInt();
            }
            QString tmp=firstDifLine;
            QString tmp1=tmp.left(3);
            tmp.remove(0,4);
            QString tmp2=tmp.left(2);
            hours=tmp1.toInt();
            minutes=tmp2.toInt();
            minutes+=hours*60;
            qDebug()<<"caseline"<<caseline;
            qDebug()<<"casenum"<<casenum;
            qDebug()<<"firstDifLine"<<firstDifLine;
            qDebug()<<tmp;
            qDebug()<<tmp1;
            qDebug()<<tmp2;
            qDebug()<<hours<<"  "<<minutes;
            ////////////////////////////////////////////////////////////////////////////////////////////
            /// 可以直接使用的变量有                                                                    ///
            /// int casenum;表示第一次出现错误的case数                                                  ///
            /// int minutes;表示第一次出现错误的前一个时刻,由hours*60+minutes得到。例：016:40则minutes=1000///
            ///////////////////////////////////////////////////////////////////////////////////////////
            //
            Time=minutes;
            Casenum=casenum;
            ui->totestbt->show();//
}
