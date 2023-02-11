#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    edit = new EDateTimeEdit(this);

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
        qDebug() << __PRETTY_FUNCTION__ << dateTime;
    });
}

Widget::~Widget()
{
    delete ui;
}

