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

    /* DATABASE QUERIES */
    //Udfører Queries. - Lavet lidt dumt. Det er SQLDatabasen der sikre, at der ikke sker fejl :S
    mSplashScreen->showMessage("Opretter tabeller i database",Qt::AlignLeft,Qt::white);

    qDebug() << "*  OPSTART SQL QUERIES *";
    qDebug() << " - Bemærk: Hvis de fejler, kan det skyldes, at alt er i orden!";
    //Tilføjer nye
    dbmgr->exec("CREATE TABLE `tblPersoner` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT);");

    dbmgr->exec("CREATE TABLE `powerpauses` (`id`   INTEGER PRIMARY KEY AUTOINCREMENT);");

    dbmgr->exec("CREATE TABLE `startbythings` (`text` TEXT)");


    //Opdaterer ekisterende
    //tblPersoner
    dbmgr->exec("ALTER TABLE tblPersoner ADD COLUMN id INTEGER PRIMARY KEY AUTOINCREMENT;");
    dbmgr->exec("ALTER TABLE tblPersoner ADD COLUMN hold TEXT;");
    dbmgr->exec("ALTER TABLE tblPersoner ADD COLUMN navn TEXT;");

    //startbythings
    dbmgr->exec("ALTER TABLE startbythings ADD COLUMN text TEXT;");

    //PowerPause
    dbmgr->exec("ALTER TABLE powerpauses ADD COLUMN id INTEGER PRIMARY KEY AUTOINCREMENT;");
    dbmgr->exec("ALTER TABLE powerpauses ADD COLUMN isActive INTEGER DEFAULT 1;");
    dbmgr->exec("ALTER TABLE powerpauses ADD COLUMN title TEXT;");
    dbmgr->exec("ALTER TABLE powerpauses ADD COLUMN helptext TEXT;");
    dbmgr->exec("ALTER TABLE powerpauses ADD COLUMN image BLOB;");


    //Lukker DB
    dbmgr->closeAndRemoveDatabase();
    qDebug() << "*  OPSTART SQL QUERIES SLUT!*";

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
