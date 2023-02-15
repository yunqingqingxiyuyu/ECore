#include <QApplication>

#include "widget.h"

#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QComboBox box;
    box.addItem("0");
    box.addItem("1");
    box.addItem("2");
    box.addItem("3");
    box.show();

    Widget w;

    w.show();
    return a.exec();
}
