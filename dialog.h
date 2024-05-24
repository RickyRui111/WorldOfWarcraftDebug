#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMap>
QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
//下面的是自己写的
public slots:
    void compareText();//文本对比的主要函数
};
#endif // DIALOG_H
