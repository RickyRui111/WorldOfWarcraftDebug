#include "inputwidget.h"
#include "ui_inputwidget.h"
#include"QTextDocument"
#include"compare.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include"QMessageBox"
#include<vector>
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
    QString & data=inputstr;
    QStringList lines = data.split(QRegExp("\n"), QString::SkipEmptyParts);
    std::vector<int> intArray;
    for (const QString &line : lines) {
        // 按空格分割每行的数字，并转换为 int
        QStringList numbers = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for (const QString &numberStr : numbers) {
            bool ok;
            int number = numberStr.toInt(&ok); // 尝试转换字符串为整数
            if (ok) {
                intArray.push_back(number); // 如果转换成功，添加到一维数组中
            } else {
                // 处理转换失败的情况（例如，打印错误消息）
                qDebug() << "无法将字符串转换为整数：" << numberStr;
                QMessageBox::warning(this, "错误", "输入不符合格式，请只输入数字！");
                return;
            }
        }
    }
    if(intArray.size()!=(intArray[0]*15+1)){
        qDebug() << "数据格式不正确";
        QMessageBox::warning(this, "错误", "输入不符合格式，请检查数据！");
        return;
    }
    compare* compw=new compare(w,this);
    compw->sendData(inputstr);
    compw->show();

}

void inputwidget::on_pushButton_clicked()
{
    ui->inputtextEdit->setPlainText("1\n20 1 10 10 1000\n20 20 30 10 20\n5 5 5 5 5");
}
QString readTxtFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << filePath;
        return QString(); // 或者抛出一个异常
    }

    QTextStream in(&file);
    QString content;
    while (!in.atEnd()) {
        content += in.readLine() + "\n"; // 保留换行符
    }

    file.close();
    return content;
}
void inputwidget::on_pushButton_2_clicked()
{
    QString filePath = ":/images/QTpictures/input.txt";
    QString str = readTxtFile(filePath);
    ui->inputtextEdit->setPlainText(str);
}
