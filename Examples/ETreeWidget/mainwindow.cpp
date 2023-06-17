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

    EGridModel *model = new EGridModel;
    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    model->addProperty("name");
    model->setupModelData(array);
    file.close();
    EGridWidget *view = new EGridWidget();
    view->setModel(model);
    QFont font = view->labelFont();
    font.setPixelSize(font.pointSizeF() + 2);
    font.setBold(true);
    view->setLabelFormat("---[[name]][test标签]---///");
    view->setLabelFont(font);
    view->setLabelAligment(Qt::AlignRight);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

