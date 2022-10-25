#include "mdbrowser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mdBrowser w;
    w.show();
    return a.exec();
}
