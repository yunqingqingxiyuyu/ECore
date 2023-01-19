#include "lineedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineEdit w;
    w.show();
    return a.exec();
}
