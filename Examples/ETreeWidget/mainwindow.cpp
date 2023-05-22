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
    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    model->setupModelData(array);
    file.close();
    ETreeWidget *view = new ETreeWidget();
    view->setModel(model);
    QFont font = view->labelFont();
    font.setPixelSize(font.pointSizeF() + 2);
    font.setBold(true);
    view->setLabelFont(font);
    view->setLabelAligment(Qt::AlignRight);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

