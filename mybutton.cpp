#include "mybutton.h"


Mybutton::Mybutton(QWidget *parent,
                   QString name,
                            QIcon image,
                            bool mask,
                            bool music
                            ):QPushButton(name,parent)
{
 /*basic功能：
    1. 初始化一个悬浮弹窗xuanfu 垂直布局 在按钮下方 安装eventfilter
    2. 可以初始化name image mask music
    */
    //初始化按钮：

    //初始化页面：
    xuanfu=new QWidget(nullptr,Qt::ToolTip);
    //Qt::ToolTip 用于指定创建的窗口是一个工具提示窗口
    xuanfu->setWindowFlag(Qt::Popup);

    layout=new QVBoxLayout(xuanfu);

//    QLabel *label4=new QLabel("herotype:卢本伟",xuanfu);
//    QLabel *label = new QLabel("health: 123",xuanfu);
//    QLabel *label2 = new QLabel("attack:999",xuanfu);
//    QLabel *label3 = new QLabel("weapon:屠龙宝刀",xuanfu);//这个label 时xuanfu的！
//    QPushButton *button=new QPushButton("我还可以有按钮",xuanfu);
//    layout->addWidget(label);
//    layout->addWidget(label2);
//    layout->addWidget(label3);
//    layout->addWidget(label4);
//    layout->addWidget(button);

    xuanfu->setLayout(layout);
    xuanfu->adjustSize();//根据内容多少调整页面大小

    xuanfu->installEventFilter(this);
}

void Mybutton::enterEvent(QEvent *event)//注意这个基类的参数是 QEnterEvent *
{//不知道是不是版本不一样的问题？ 那之后还要改？？
    QPushButton::enterEvent(event);
    //调整位置， 显示
    QPoint globalPos=mapToGlobal(QPoint(0,height()));
    xuanfu->move(globalPos);
    xuanfu->show();
}

void Mybutton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    QPoint globalPos = QCursor::pos(); // 获取全局鼠标位置
    QPoint localPos = xuanfu->mapFromGlobal(globalPos); // 转换为本地坐标
    qDebug() << "Global position:" << globalPos << "Local position:" << localPos << "Geometry:" << xuanfu->geometry();

    QTimer::singleShot(200, this, [this]() {
        // 检查鼠标位置是否在 xuanfu 的几何区域内
        if (!xuanfu->geometry().contains(QCursor::pos())) {
            xuanfu->hide();
        }
    });

    // if(!xuanfu->geometry().contains(localPos))
    // {
    //     qDebug() << "Hiding xuanfu";
    //     qDebug()<<"Button (local) geometry:"<<this->geometry();
    //     QPoint globalButton = mapToGlobal(QPoint(0,0));//后者得到的是按钮的局部topleft 用函数转换全局
    //     qDebug()<<"Button global top left:"<<globalButton;
    //     qDebug()<<"xuanfu geometry:"<<this->xuanfu->geometry();
    //     xuanfu->hide();
    // }

    // else {
    //     qDebug() << "Not hiding xuanfu";
    // }
}

bool Mybutton::eventFilter(QObject *watched, QEvent *event) {
    if (watched == xuanfu && event->type() == QEvent::Leave) {
        xuanfu->hide();
        return true;
    }
    return QPushButton::eventFilter(watched, event);
}
