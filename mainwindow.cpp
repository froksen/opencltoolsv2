#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabs/countdowntimer.h"
#include "tabs/selectorfinger.h"
//#include "tabs/orderchooser.h"
#include "tabs/selectorrandomvalue.h"
#include "tabs/selectorthing.h"
#include "tabs/spinboard.h"
#include "tabs/powerpausepicker.h"
//#include "tabs/CooperativeLearning/teamplate.h"
#include "tabs/groupcreator.h"
#include <QMessageBox>
#include <QMediaPlayer>
#include <QDate>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
//    //ui->tabWidget->addTab(new TeamPlate,"CL: Teamplade");
    ui->tabWidget->setCurrentIndex(6);


    ui->mainToolBar->setHidden(true);


    //Fødselsdag
    QDate bDate = QDate(1988,9,11);
    QDate curDate = QDate::currentDate();

    ui->menuF_DSELSDAG_11_SEPTEMBER->menuAction()->setVisible(false);
    if(bDate.month() == curDate.month() && curDate.day() == bDate.day()){
        ui->menuF_DSELSDAG_11_SEPTEMBER->menuAction()->setVisible(true);
        qDebug() << "YAY! Oles fødselsdag!";
    }

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
           "(c) 2016 <br>"
           "Licens: GPL v2";

    QMessageBox::information(this,"Om",text);
}

void MainWindow::on_actionH_r_sangen_triggered()
{
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/of.mp3"));
    player->setVolume(100);
    player->play();

    QString text;
    text = "I dag er det Oles fødselsdag! Hurra Hurra!";
    QMessageBox::information(this,"Oles fødelsdag",text);

    player->stop();
}

void MainWindow::on_actionFuldsk_rm_Vindue_triggered()
{
    if(windowState() == Qt::WindowFullScreen){
        setWindowState(Qt::WindowNoState);
        return;
    }
    setWindowState(Qt::WindowFullScreen);
}

DatabaseManager *MainWindow::databaseManager() const
{
    return _databaseManager;
}

void MainWindow::setDatabaseManager(DatabaseManager *databaseManager)
{
    _databaseManager = databaseManager;
}
