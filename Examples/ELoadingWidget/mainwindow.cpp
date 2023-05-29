#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include <QPushButton>
#include <QHBoxLayout>
#include <ESingleton>
#include "ELoadingWidget"
#include <QDialog>

void print()
{
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *w = new QWidget;
    QHBoxLayout *lay = new QHBoxLayout;
    QVBoxLayout *lay2 = new QVBoxLayout;

    QPushButton *button = new QPushButton("按下按钮，弹出信",this);
    QPushButton *button2 = new QPushButton("按下按钮2，弹出信",this);
    QPushButton *button3 = new QPushButton("按下按钮2，弹出信",this);
    QPushButton *button4 = new QPushButton("按下按钮2，弹出信",this);
    w2 = new QWidget;
    w2->setStyleSheet("QWidget{background-color:green;}");
    button->setStyleSheet("QPushButton{background-color:green;}");
    connect(button,&QPushButton::clicked,this,[=](){
        QTimer::singleShot(10*1000,this,[=](){
            m_loop.quit();
        });
        this->noBlockingTest();
    });

    connect(button2,&QPushButton::clicked,this,[=](){
        qDebug() << __PRETTY_FUNCTION__;
        ES(ELoadingWidget)->setParent(this);
        ES(ELoadingWidget)->raise();
        ES(ELoadingWidget)->show(10 * 1000);
    });

    connect(button3,&QPushButton::clicked,this,[&](){
        qDebug() << __PRETTY_FUNCTION__;
        QDialog *d = new QDialog;

        d->resize(700,600);
        d->show();
        ES(ELoadingWidget)->setParent(d);
        qDebug() << __PRETTY_FUNCTION__ << w2 << this;
        ES(ELoadingWidget)->show();
        ES(ELoadingWidget)->setText("hello");
        ES(ELoadingWidget)->setScaledSize(QSize(100,100));
        QFont font = ES(ELoadingWidget)->font();
        font.setPixelSize(30);
        ES(ELoadingWidget)->setFont(font);
        ES(ELoadingWidget)->setMaxShowTime(10 * 1000);
    });

    connect(button4,&QPushButton::clicked,this,[=](){
        ES(ELoadingWidget)->hide();
    });

    lay2->addWidget(w2);

    lay->addWidget(button);
    lay->addWidget(button2);
    lay->addWidget(button3);
    lay->addWidget(button4);
    lay->addLayout(lay2);
    w->setLayout(lay);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::noBlockingTest()
{

    do{
        //此处弹出对话框，期间不影响后续代码执行，但是不响应界面操作
        ELoadingWidget w("qwww",1 *1000,this);//("111111111111111",10 * 1000,this);
//        w.setFileName("C:\\Users\\zl\\Desktop\\loading2.gif");
        m_loop.exec();

    }while (false);

    //在函数结束时自动关闭对话框
}
