#ifndef INCITY_H
#define INCITY_H

#include <QWidget>
#include"CaseInfo.h"
#include"inwarrior.h"
namespace Ui {
class incity;
}

class incity : public QWidget
{
    Q_OBJECT

public:
    inwarrior* bw;
    inwarrior* rw;
    bool rhavew=0;
    bool bhavew=0;
    explicit incity(const City &c,QWidget *parent = nullptr);
    void setw(const Warrior&w);
    void set(const City &c);
    ~incity();

private slots:
    void on_rpushButton_clicked();

    void on_bpushButton_clicked();

private:
    Ui::incity *ui;
};

#endif // INCITY_H
