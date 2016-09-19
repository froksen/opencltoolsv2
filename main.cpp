#include "mainwindow.h"
#include <QApplication>
//#include <QStyleFactory>
//#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //qDebug() << QStyleFactory::keys();
    //a.setStyle(QStyleFactory::create("WindowsVista"));

    MainWindow w;
    w.show();
    return a.exec();
}
