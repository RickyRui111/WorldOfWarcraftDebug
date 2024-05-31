#ifndef INWARRIOR_H
#define INWARRIOR_H

#include <QWidget>
#include<CaseInfo.h>
namespace Ui {
class inwarrior;
}

class inwarrior : public QWidget
{
    Q_OBJECT

public:    
    explicit inwarrior(Warrior& w,QWidget *parent = nullptr);
    void set(const Warrior & w);
    ~inwarrior();

private:
    Ui::inwarrior *ui;
};

#endif // INWARRIOR_H
