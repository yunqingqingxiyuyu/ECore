#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "singleton.h"

#include <thread>

void func()
{
    Singleton *obj = ESingleton<Singleton>::getInstance();

    Singleton *obj2 = ESingleton<Singleton>::getInstance();

    Singleton *obj3 = ES(Singleton);

    qDebug() << obj << obj2 << obj3;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::thread T1(func);
    std::thread T2(func);
    std::thread T3(func);

    T1.join();
    T2.join();
    T3.join();
}

MainWindow::~MainWindow()
{
    delete ui;
}

