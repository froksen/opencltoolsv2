#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
#include "QSqlDatabase"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

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

    //************************************
    //* DATABASE
    //*************************************
    //Forbindelsen
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    if(!db.open()){
        mSplashScreen->showMessage("Fejl ved indlæsning af database!",Qt::AlignLeft,Qt::white);
        QMessageBox::critical(0,"Fejl","Der skete en fejl ved indlæsning af databasen. Alle funktioner er måske ikke tilgængelige.\nFejlbeskrivelse: " + db.lastError().text(),QMessageBox::Ok);
    }

    a.processEvents(); //Sikre, at musen kan trykkes.

    /* DATABASE QUERIES */
    //Udfører Queries. - Lavet lidt dumt. Det er SQLDatabasen der sikre, at der ikke sker fejl :S
    mSplashScreen->showMessage("Opretter tabeller i database",Qt::AlignLeft,Qt::white);

    QStringList dbTables = db.tables();
    QStringList defaultDbTables;
    defaultDbTables << "tblPersoner" << "powerpauses" << "startbythings";

    foreach(QString tableName, defaultDbTables){
        if(!dbTables.contains(tableName)){
            QString qry = QString("CREATE TABLE '%1' (`id`	INTEGER PRIMARY KEY AUTOINCREMENT);").arg(tableName);
            qDebug() << "Database tabel" << tableName << "ikke fundet." << "Opretter tabel.";
            qDebug() << "Udfører query" << qry;
            db.exec(qry);

            if(db.lastError().text() != " "){
                qDebug() << "Oprettelse af tabel" << tableName << "mislykkedes." << "Query:" << qry << "Fejl:"<< db.lastError().text();
            }
        }
    }

    //Tilføjer kolonnenavne
    QStringList alterQrys;
    alterQrys << "ALTER TABLE tblPersoner ADD COLUMN id INTEGER PRIMARY KEY AUTOINCREMENT;"
             <<"ALTER TABLE tblPersoner ADD COLUMN hold TEXT;"
            <<"ALTER TABLE tblPersoner ADD COLUMN navn TEXT;"
           << "ALTER TABLE startbythings ADD COLUMN text TEXT;"
           <<"ALTER TABLE powerpauses ADD COLUMN id INTEGER PRIMARY KEY AUTOINCREMENT;"
          <<"ALTER TABLE powerpauses ADD COLUMN isActive INTEGER DEFAULT 1;"
         <<"ALTER TABLE powerpauses ADD COLUMN title TEXT;"
        <<"ALTER TABLE powerpauses ADD COLUMN helptext TEXT;"
       <<"ALTER TABLE powerpauses ADD COLUMN image BLOB;";

    foreach(QString alterQry, alterQrys){
        db.exec(alterQry);

        if(db.lastError().text() != " "){
            qDebug() << "Fejl ved udførelse af query" << alterQry <<". Fejlbeskrivelse:" << db.lastError().text();
        }
    }

    mSplashScreen->showMessage("Indlæser...",Qt::AlignLeft,Qt::white);

    //Hoved vinduet
    MainWindow w;

    //Viser GUI
    mSplashScreen->finish(&w);
    w.show();

    return a.exec();
}
