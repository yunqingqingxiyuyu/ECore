#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

#include "ESingleton"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    auto edit = ESingleton<EDateTimeEdit>::getInstance();
    qDebug() << "对象地址" << edit;
    edit = ESingleton<EDateTimeEdit>::getInstance();
    qDebug() << "对象地址" << edit;

    edit = new EDateTimeEdit(this);
    edit->clearDisplayText();
    qDebug() << edit->text();

    QPushButton *button = new QPushButton;
    QPushButton *button2 = new QPushButton("111111111");

    QVBoxLayout *lay = new QVBoxLayout;

    lay->addWidget(edit);
    lay->addWidget(button);
    lay->addWidget(button2);
    setLayout(lay);

    connect(button,&QPushButton::clicked,this,[=](){
        QVariant v ="";
        qDebug()  << edit->text()<<endl
                  << edit->date() << endl << edit->date().isNull() << edit->date().isValid() << endl
                  << edit->dateTime()<<endl
                  << edit->time()<<endl
                  << edit->dateTime().toString("yyyy-MM-dd hh:mm:ss") << endl
                  << edit->dateTime().isValid()
                  << QDateTime::fromString(edit->text())
                  << edit->displayFormat()
                  << edit->maximumDate()
                  << v.toDate()
                  << v.toDateTime()
                  << v.toDateTime().toString("yyyy-MM-dd hh:mm:ss")
                  << "---------------------" << endl
                    ;

         edit->setDisplayFormat("yyyy-MM-dd");
         qDebug() << edit->displayFormat() << endl ;
    });

    connect(edit,&EDateTimeEdit::dateTimeChanged,this,[=](const QDateTime &dateTime){
    });

    connect(button2,&QPushButton::clicked,this,[=](){
        ed = ESingleton<EDateTimeEdit>::getInstance();
        ed->setParent(this);
        qDebug() << ed;

        ed->show();
    });

    edit->clearDisplayText();
}

Widget::~Widget()
{
    delete ui;
}

