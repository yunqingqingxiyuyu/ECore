#include "widget.h"
#include "ui_widget.h"

#include <ESecretComboBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->comboBox->setTopLevel(ui->comboBox->toLevel("机密"));
    ui->comboBox_2->addItem(4,"内部");

    //清除原来的选项
    ui->editor->clear();

    //自己创建一个一个表
    //密级值可以不连续，但是密级越高，值就应当越大。
    QMap<int ,QString> levels{
        {0,"非密"},
        {1,"内部"},
        {2,"秘密"},
        {11,"机密"},
        {33,"绝密"}
    };

    ui->editor->addItems(levels);

}

Widget::~Widget()
{
    delete ui;
}

