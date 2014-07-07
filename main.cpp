#include "mainwindow.h"
#include <QApplication>
#include <event.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ui.setupUi(&w);

    event filter;
    a.installEventFilter(&filter);
    w.show();

    return a.exec();
}
