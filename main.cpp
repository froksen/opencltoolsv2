#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Splashskærmen
    QSplashScreen *mSplashScreen = new QSplashScreen();
    mSplashScreen->setPixmap(QPixmap(":/img/logo.png"));
    mSplashScreen->showMessage("Indlæser programmet",Qt::AlignLeft,Qt::white);
    a.processEvents(); //Sikre, at musen kan trykkes.
    mSplashScreen->show(); //Viser splash

    mSplashScreen->showMessage("Indlæser...",Qt::AlignLeft,Qt::white);

    //Hoved vinduet
    MainWindow w;

    //Viser GUI
    mSplashScreen->finish(&w);
    w.show();

    return a.exec();
}
