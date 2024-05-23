#ifndef COMPARE_H
#define COMPARE_H

#include <QWidget>

namespace Ui {
class compare;
}

class compare : public QWidget
{
    Q_OBJECT

public:
    int Time;
    QString DATA;

public:
    explicit compare(QWidget *parent = nullptr);
    void sendData(QString data);
    ~compare();

private slots:
    void on_totestbt_clicked();

    void on_confirmbt_clicked();

private:
    Ui::compare *ui;
};

#endif // COMPARE_H
