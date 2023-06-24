#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <EGridWidget>
#include <EGridModel>
#include <ELoadingWidget>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QHeaderView>

#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/tree_json.json");
    file.open(QIODevice::ReadOnly);

//    EGridWidget *view = new EGridWidget();
//    view->verticalHeader()->show();

    QTableView *view = new QTableView;

    EGridModel *model = new EGridModel(2);
    view->setModel(model);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    model->setHeaderData(0,Qt::Horizontal,"fiestColomn");
    model->setHeaderData(1,Qt::Horizontal,"secondTitle");

    model->addColumnProperty(0,"column0");
    model->addColumnProperty(1,"column1");
    model->setupModelData(array);
    file.close();

//    QFont font = view->labelFont();
//    font.setPixelSize(font.pointSizeF() + 2);
//    font.setBold(true);
//    view->setLabelFormat(0,"---[[name]][column1]---///");
//    view->setLabelFont(font);
//    view->setLabelAligment(Qt::AlignRight);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

