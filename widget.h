#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_inputbt_clicked();

    void on_tipsbt_clicked();

    void on_exitbt_clicked();

private:
    Ui::Widget *ui;
    QLabel *backgroundl;
};
#endif // WIDGET_H
