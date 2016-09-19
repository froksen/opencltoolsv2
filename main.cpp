#include "mainwindow.h"
#include <QApplication>
//#include <QStyleFactory>
//#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
#include "classes/databasemanager.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //qDebug() << QStyleFactory::keys();
    //a.setStyle(QStyleFactory::create("WindowsVista"));

    //Hoved vinduet
    //MainWindow w;


    QSplashScreen *mSplashScreen = new QSplashScreen();
    mSplashScreen->setPixmap(QPixmap(":/img/fingerFive.png"));
    mSplashScreen->showMessage("Indlæser programmet");
    a.processEvents(); //Sikre, at musen kan trykkes.

    //DATABASE
    DatabaseManager *dbmgr = new DatabaseManager();
    dbmgr->setCurrentDatabaseFile("db.sqlite");
    if(!dbmgr->open()){
        QMessageBox::critical(0,"Indlæsningsfejl",dbmgr->splashScreenText());
        a.quit();
        a.exit(EXIT_FAILURE);
    }
    mSplashScreen->showMessage(dbmgr->splashScreenText());
    a.processEvents(); //Sikre, at musen kan trykkes.

    mSplashScreen->show(); //Viser splash



    //QTimer::singleShot(1200,&w,SLOT(show())); //Sikre, at splashscreenen vises mindst 1200 ms

    //mSplashScreen->finish(&w); //Når MainWindow er loaded, da lukkes splash automatisk.

    return a.exec();
}
