#include <QApplication>

#include "widget.h"

#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    w.show();
    return a.exec();
}
