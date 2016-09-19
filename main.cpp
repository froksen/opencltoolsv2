#include "mainwindow.h"
#include <QApplication>
//#include <QStyleFactory>
//#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //qDebug() << QStyleFactory::keys();
    //a.setStyle(QStyleFactory::create("WindowsVista"));

    //Hoved vinduet
    MainWindow w;

    QSplashScreen *mSplashScreen = new QSplashScreen();
    mSplashScreen->setPixmap(QPixmap(":/img/fingerFive.png"));
    mSplashScreen->showMessage("Indlæser BLBLABLA");
    a.processEvents(); //Sikre, at musen kan trykkes.

    mSplashScreen->show(); //Viser splash
    QTimer::singleShot(1200,&w,SLOT(show())); //Sikre, at splashscreenen vises mindst 1200 ms

    mSplashScreen->finish(&w); //Når MainWindow er loaded, da lukkes splash automatisk.

    return a.exec();
}
