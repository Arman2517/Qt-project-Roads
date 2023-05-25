#include "mainwindow.h"
#include "mypoint.h"
#include <QApplication>
#include <QLabel>
#include <QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
