#include "lineedit.h"
#include "ui_lineedit.h"

#include <ELineEdit>

#include <QLabel>
#include <QGridLayout>

LineEdit::LineEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LineEdit)
{
    ui->setupUi(this);

    ELineEdit *lineEdit = new ELineEdit("  获取设置自动把字符串的前后空格清除   ");
    ELineEdit *lineEdit2 = new ELineEdit();
    lineEdit2->setPlaceholderText("默认清除空格");
    lineEdit2->setSearchButtonEnabled(false);
    ELineEdit *lineEdit3 = new ELineEdit();
    lineEdit3->setPlaceholderText("默认清除空格");
    lineEdit3->setClearButtonEnabled(false);
    QLabel *searchLabel = new QLabel("查找显示");
    QLineEdit *displayLabel = new QLineEdit();

    QGridLayout *mainLay = new QGridLayout;
    mainLay->addWidget(lineEdit,0,0,1,2);
    mainLay->addWidget(lineEdit2,1,0,1,2);
    mainLay->addWidget(lineEdit3,2,0,1,2);
    mainLay->addWidget(searchLabel,3,0,1,1);
    mainLay->addWidget(displayLabel,3,1,1,1);
    setLayout(mainLay);

    connect(lineEdit,&ELineEdit::searchPressed,this,[=](const QString &text){
        displayLabel->setText(text);
    });

    connect(lineEdit,&ELineEdit::textChanged,this,[=](const QString &text){
        displayLabel->setText(text);
    });
}

LineEdit::~LineEdit()
{
    delete ui;
}

