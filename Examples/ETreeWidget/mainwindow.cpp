#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <EGridWidget>
#include <EGridModel>
#include <ELoadingWidget>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/tree_json.json");
    file.open(QIODevice::ReadOnly);

    EGridWidget *view = new EGridWidget();

    EGridModel *model = new EGridModel(2);
    view->setModel(model);

    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    model->setHeaderData(0,Qt::Horizontal,"fiestColomn");
    model->addColumnProperty(0,"column0");
    model->addColumnProperty(1,"column1");
    model->setupModelData(array);
    model->setHeaderData(1,Qt::Horizontal,"fiestColomn");
    file.close();



    QFont font = view->labelFont();
    font.setPixelSize(font.pointSizeF() + 2);
    font.setBold(true);
    view->setLabelFormat(0,"---[[name]][column1]---///");
    view->setLabelFont(font);
    view->setLabelAligment(Qt::AlignRight);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

