#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ETreeWidget>
#include <ETreeModel>
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

    ETreeModel *model = new ETreeModel;
//    ELoadingWidget *w = new ELoadingWidget(this);
    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    model->setupModelData(array);
    file.close();
    QTreeView *view = new QTreeView;
    view->setModel(model);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

