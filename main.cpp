#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
#include "classes/databasemanager.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //STYLE
    //qDebug() << QStyleFactory::keys();
    //a.setStyle(QStyleFactory::create("Windows"));


    //Splashskærmen
    QSplashScreen *mSplashScreen = new QSplashScreen();
    mSplashScreen->setPixmap(QPixmap(":/img/logo.png"));
    mSplashScreen->showMessage("Indlæser programmet",Qt::AlignLeft,Qt::white);
    a.processEvents(); //Sikre, at musen kan trykkes.
    mSplashScreen->show(); //Viser splash

    //DATABASE
    DatabaseManager *dbmgr = new DatabaseManager();
    dbmgr->setCurrentDatabaseFile("db.sqlite");
    if(!dbmgr->open()){
        QMessageBox::critical(0,"Indlæsningsfejl",dbmgr->splashScreenText());
        a.quit();
        a.exit(EXIT_FAILURE);
    }
    mSplashScreen->showMessage(dbmgr->splashScreenText(),Qt::AlignLeft,Qt::white);
    a.processEvents(); //Sikre, at musen kan trykkes.

    //Hvis den er åben, skal den sikre, at der er oprettet disse tabeller i DB.
    QString qryGroupCreator =   "CREATE TABLE `tblPersoner` ("
                                          "`id`	INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "`navn`	TEXT"
                                      ");";

    QString qryPowerPause = "CREATE TABLE `powerpauses` ("
                              "`id`	INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "`isActive`	INTEGER DEFAULT 1,"
                               "`title`	TEXT,"
                              "`helptext`	TEXT,"
                              "`image`	BLOB);";

    QString qrySelectorThing = "CREATE TABLE `startbythings` (`text` TEXT)";

    dbmgr->execMultibleList().append(qryGroupCreator);
    dbmgr->execMultibleList().append(qryPowerPause);
    //dbmgr->execMultibleList().append(qrySelectorThing);
    dbmgr->exec(qrySelectorThing);

    mSplashScreen->showMessage("Opretter tabeller i database",Qt::AlignLeft,Qt::white);

    if(!dbmgr->execMultible()){
        QMessageBox::critical(0,"Indlæsningsfejl ved tabeller",dbmgr->splashScreenText());
        a.quit();
        a.exit(EXIT_FAILURE);
    }


    //Lukker DB
    dbmgr->closeAndRemoveDatabase();

    mSplashScreen->showMessage("Alle tabeller oprettet!",Qt::AlignLeft,Qt::white);

    mSplashScreen->showMessage("Indlæser...",Qt::AlignLeft,Qt::white);

    //Hoved vinduet
    MainWindow w;

    //Sætter dbmgr til MainWindow
    //w.setDatabaseManager(dbmgr);

    //Viser GUI
    mSplashScreen->finish(&w);
    w.show();

    //QTimer::singleShot(2200,&w,SLOT(show())); //Sikre, at splashscreenen vises mindst 1200 ms

    return a.exec();
}
