#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "elineedit.h"
#include <QLineEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_lineEdit = new ELineEdit;
    m_lineEdit->setText("   11122   ");
    m_lineEdit->show();
//    setCentralWidget(m_lineEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

