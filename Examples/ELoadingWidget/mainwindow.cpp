#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include <QPushButton>
#include <synchapi.h>
#include "ELoadingWidget"

void print()
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << __PRETTY_FUNCTION__;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *button = new QPushButton("按下按钮，弹出信息",this);
    button->setStyleSheet("QPushButton{background-color:green;}");
    connect(button,&QPushButton::clicked,this,[=](){
        QTimer::singleShot(10*1000,this,[=](){
            m_loop.quit();
            m_loop.exec();
            m_loop.quit();
        });
        this->noBlockingTest();
    });

}

MainWindow::~MainWindow()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete ui;
}


void MainWindow::noBlockingTest()
{

    do{
        //此处弹出对话框，期间不影响后续代码执行，但是不响应界面操作
        ELoadingWidget w(this);//("111111111111111",10 * 1000,this);
        m_loop.exec();

    }while (false);

    //在函数结束时自动关闭对话框
}
