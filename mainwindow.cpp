#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabs/countdowntimer.h"
#include "tabs/selectorfinger.h"
//#include "tabs/orderchooser.h"
#include "tabs/selectorrandomvalue.h"
#include "tabs/selectorthing.h"
#include "tabs/spinboard.h"
#include "tabs/powerpausepicker.h"
#include "tabs/stopwatch.h"
#include "tabs/clock.h"
#include "tabs/groupcreator.h"
#include <QMessageBox>
#include <QMediaPlayer>
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //DB
    initDB();
    ui->setupUi(this);

    //Fanebladene
    qDebug() << "Ur";
    ui->tabWidget->addTab(new Clock,"Ur");
    qDebug() << "Stopur";
    ui->tabWidget->addTab(new StopWatch,"Stopur");
    qDebug() << "Nedtællingsur";
    ui->tabWidget->addTab(new CountDownTimer,"Nedtællingsur");
    qDebug() << "Tilfældigt tal";
    ui->tabWidget->addTab(new SelectorRandomValue,"Tilfældigt tal");
    qDebug() << "Vælger (Hånd)";
    ui->tabWidget->addTab(new SelectorFinger,"Vælger (Hånd)");
    qDebug() << "Vælger (Ting)";
    ui->tabWidget->addTab(new SelectorThing,"Vælger (Ting)");
    qDebug() << "Vælger (Tal)";
    ui->tabWidget->addTab(new SpinBoard,"Vælger (Tal)");
    qDebug() << "PowerPause vælger";
    ui->tabWidget->addTab(new PowerPausePicker,"PowerPause vælger");
    qDebug() << "Gruppeskaber";
    ui->tabWidget->addTab(new GroupCreator,"Gruppeskaber");
    //ui->tabWidget->addTab(new OrderChooser,"Gl. Gruppeskaber");
    ui->tabWidget->setCurrentIndex(0);


    ui->mainToolBar->setHidden(true);

//    CountDownTimer *cdt = new CountDownTimer(this);
//    cdt->setGeometry(0,0,this->width(),this->height());
//    cdt->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAfslut_triggered()
{
   this->close();
}

void MainWindow::on_actionOm_triggered()
{
    QString text;
    text = "Ole Dahl Frandsen <br>"
           "OpenCL Tools (c) 2016 <br>"
           "License: GPL v2"
            "<br>"
            "<br>"
            "alarm.mp3 (Temple Bell sound) by Mike Koenig<br>"
            "License: Attribution 3.0"
           "<br>"
           "<br>"
            "All other trademarks, servicemarks, registered trademarks, and registered servicemarks are the property of their respective owners";

    QMessageBox::information(this,"Om",text);
}

void MainWindow::on_actionFuldsk_rm_Vindue_triggered()
{
    if(windowState() == Qt::WindowFullScreen){
        setWindowState(Qt::WindowNoState);
        return;
    }
    setWindowState(Qt::WindowFullScreen);
}

void MainWindow::initDB()
{
    //************************************
    //* DATABASE
    //*************************************
    //Forbindelsen
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","default_connection");
    db.setDatabaseName("db.sqlite");
    if(!db.open()){
        QMessageBox::critical(0,"Fejl","Der skete en fejl ved indlæsning af databasen. Alle funktioner er måske ikke tilgængelige.\nFejlbeskrivelse: " + db.lastError().text(),QMessageBox::Ok);
    }

    /* DATABASE QUERIES */
    //Udfører Queries. - Lavet lidt dumt. Det er SQLDatabasen der sikre, at der ikke sker fejl :S

    QStringList dbTables = db.tables();
    QStringList defaultDbTables;
    defaultDbTables << "tblPersoner" << "powerpauses" << "startbythings";

    foreach(QString tableName, defaultDbTables){
        if(!dbTables.contains(tableName)){
            QString qry = QString("CREATE TABLE '%1' (`id`	INTEGER PRIMARY KEY AUTOINCREMENT);").arg(tableName);
            qDebug() << "Database tabel" << tableName << "ikke fundet." << "Opretter tabel.";
            qDebug() << "Udfører query" << qry;
            db.exec(qry);

            if(db.lastError().type() != QSqlError::NoError){
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

        if(db.lastError().type() != QSqlError::NoError){
            qDebug() << "Fejl ved udførelse af query" << alterQry <<". Fejl:" << db.lastError().number() << "Beskrivelse:" << db.lastError().text();
        }
    }
}

DatabaseManager *MainWindow::databaseManager() const
{
    return _databaseManager;
}

void MainWindow::setDatabaseManager(DatabaseManager *databaseManager)
{
    _databaseManager = databaseManager;
}
