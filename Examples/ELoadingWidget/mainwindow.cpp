#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eloadingwidget.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *button = new QPushButton("按下按钮，弹出信息",this);
    button->setStyleSheet("QPushButton{background-color:green;}");
    setCentralWidget(button);
    load = new ELoadingWidget("加载中",0,this);
    connect(button,&QPushButton::clicked,this,[=](){
        if(load)
        {
            delete load;
            load = nullptr;
        }
        QMessageBox::information(this,"弹出","显示信息");
        load = new ELoadingWidget("加载中",0,this);
    });
}

MainWindow::~MainWindow()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete ui;
}

