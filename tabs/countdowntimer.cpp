#include "countdowntimer.h"
#include "ui_countdowntimer.h"
#include "dialogs/timeselector.h"
#include "dialogs/alarmselector.h"
#include <QDebug>
#include <QDateTime>
#include <QTime>
#include <QMessageBox>
#include <QFont>
#include <QBrush>
#include <QPalette>
#include <QSound>
#include <QFontDatabase>

CountDownTimer::CountDownTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownTimer)
{
    ui->setupUi(this);

    //Timere
    timer = new QTimer(this);
    tickTimer = new QTimer(this);
    tickTimer->setInterval(1);

    //Connections
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimeout())); //Timer timeout
    //connect(timer,SIGNAL(timeout()),tickTimer,SLOT(stop())); //Sikre at tickTimeren stopper, når timeren er stoppet

    connect(timer,SIGNAL(timeout()),this,SLOT(toggleButtons())); //Knapperne
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(tickTimerTimeout())); //tickTimer timeout

    setAudioPlayer(new QMediaPlayer(this));


    timerIntervalAtStart = 0;

    //Skjuler JBCountdown knappen.
    ui->cbJBEffekt->setVisible(false);

}

CountDownTimer::~CountDownTimer()
{
    delete ui;
}

void CountDownTimer::timerTimeout()
{
    qDebug() << "Timer Timeout!";

    getAudioPlayer()->stop();
    //getAudioPlayer()->setSource(QUrl::fromLocalFile(":/sounds/alarm.wav"));
    getAudioPlayer()->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath () + "/sounds/alarm.mp3"));
    getAudioPlayer()->play();

    QFont dfFont("MS Shell Dlg 2");
    dfFont.setPixelSize(ui->lblTime->font().pixelSize());
    ui->lblTime->setFont(dfFont);

    if(ui->cbLoopCountdown->isChecked()){
       on_btnStartStop_clicked();

        return;
    }

    tickTimer->stop();

    //Sikre, at der vises 00:00:00:00
    QBrush brushText;
    brushText.setColor(Qt::white);

    QBrush brushBg;
    brushBg.setColor(Qt::red);

    QPalette palette = ui->lblTime->palette();
    palette.setColor(ui->lblTime->foregroundRole(), Qt::red);
    ui->lblTime->setPalette(palette);

    ui->lblTime->setText("00:00:00");
    if(ui->view1000parts->isChecked()){
        ui->lblTime->setText("00:00:00:000");
    }


    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);

    setTimerInterval(0);
}

void CountDownTimer::tickTimerTimeout()
{
    QString timeText;

    //Trækker 3600000 (1 time i ms) fra, da der ellers vises en time for meget.
    //timeText = QDateTime::fromMSecsSinceEpoch(getTimerRemainingTime()-3600000).toString("HH:mm:ss:zzz");

    if(ui->cbJBEffekt->isChecked() && getTimerRemainingTime() <= (10*1000)){ //&& getTimerRemainingTime()%2000 == 0
        int id = QFontDatabase::addApplicationFont(":/fonts/24.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont jbFont(family);
        jbFont.setPixelSize(ui->lblTime->font().pixelSize());

        ui->lblTime->setFont(jbFont);
        qDebug() << "STATE" << getAudioPlayer()->state();
        if(getAudioPlayer()->state() != QMediaPlayer::PlayingState){
            qDebug() << "JBEffect started";
            //getAudioPlayer()->setMedia(QUrl("qrc:/sounds/jbcountdown.mp3"));
            getAudioPlayer()->setVolume(100);
            getAudioPlayer()->play();
        }
    }

    if(!ui->cbJBEffekt->isChecked()){
        QFont dfFont;
        dfFont.setPixelSize(ui->lblTime->font().pixelSize());
        ui->lblTime->setFont(dfFont);
    }

    QString timeFormat = "HH:mm:ss";
    if(ui->view1000parts->isChecked()){
        timeFormat = "HH:mm:ss:zzz";
    }
    timeText = QTime(0,0,0).addMSecs(getTimerRemainingTime()).toString(timeFormat);




    //qDebug
    qDebug() << "Resterende tid (ms):" << getTimerRemainingTime();
    qDebug() << "Resterende tid (h:mm:ss:zzz):" << timeText;

    //GUI
    ui->lblTime->setText(timeText);
    ui->progressBar->setValue(getTimerRemainingTime());
}

int CountDownTimer::getTimerInterval()
{
    return timer->interval();
}

int CountDownTimer::getTimerRemainingTime()
{
    return timer->remainingTime();
}

bool CountDownTimer::setTimerInterval(int time)
{
    //Hvis tiden ikke er gyldig
//    if(!time >0){
//        return -1;
//    }

    qDebug() << "Timer interval sat til: " << time;
    //Sætter tiden
    timer->setInterval(time);
    return 0;
}

void CountDownTimer::resizeEvent(QResizeEvent* event)
{

//    //Tilpasser teksten
    QFont font;
    font.setPixelSize(this->width()/10);
    ui->lblTime->setFont(font);
}


void CountDownTimer::toggleButtons()
{
    ui->btnReset->setEnabled(true);
    ui->btnSetInterval->setEnabled(true);
    ui->btnStartStop->setEnabled(true);
    ui->cbLoopCountdown->setEnabled(true);
    ui->cbJBEffekt->setEnabled(true);

    if(tickTimer->isActive()){
        ui->btnReset->setEnabled(false);
        ui->btnSetInterval->setEnabled(false);
        ui->cbLoopCountdown->setEnabled(false);
        ui->cbJBEffekt->setEnabled(false);
    }
}

bool CountDownTimer::runTimer()
{
    if(timer->interval()<0){
        return false;
    }

    //Starter timeren;
    timer->setSingleShot(true);
    timer->start();

    //Starter tickTimer
    tickTimer->start();

    //Knapper
    toggleButtons();

    return true;
}



void CountDownTimer::setAudioPlayer(QMediaPlayer *audioPlayer)
{
    _audioPlayer = audioPlayer;
}

QMediaPlayer *CountDownTimer::getAudioPlayer() const
{
    return _audioPlayer;
}

void CountDownTimer::on_btnStartStop_clicked()
{
    if(ui->cbJBEffekt->isChecked()){
        getAudioPlayer()->stop();
    }



    if(!getTimerInterval()>0){
        //QMessageBox::warning(this,"Mangler at sætte interval","Du mangler at sætte intervallet for nedtællingsuret!");
        on_btnSetInterval_clicked();
        return;
    }

    if(!timer->isActive()){
        qDebug () << "timer not isActive";
        runTimer();
    }
    else {
        setTimerInterval(getTimerRemainingTime());
        timer->stop();
        tickTimer->stop();
    }

    //Knapper
    toggleButtons();
}

void CountDownTimer::on_btnSetInterval_clicked()
{
    //Pointer
    TimeSelector *timeselector = new TimeSelector(this);

    //Sætter tidligere valgte tid
    timeselector->setTime(timerIntervalAtStart);

    //Hvis tiden er accpeterets, da opdateres den
    if(timeselector->exec() == QDialog::Accepted){
        //Omregner fra QTime til millisecs
        timerIntervalAtStart = QTime(0,0,0).msecsTo(timeselector->getTime());
        setTimerInterval(QTime(0,0,0).msecsTo(timeselector->getTime()));

        QString timeFormat = "HH:mm:ss";
        if(ui->view1000parts->isChecked()){
            timeFormat = "HH:mm:ss:zzz";
        }

        ui->lblTime->setText(QTime(0,0,0).addMSecs(getTimerInterval()).toString(timeFormat));

        QPalette palette = ui->lblTime->palette();
        palette.setColor(ui->lblTime->foregroundRole(), Qt::black);
        ui->lblTime->setPalette(palette);

        ui->progressBar->setMaximum(timerIntervalAtStart);
    }

    //Sletter pointer
    timeselector = NULL;
    delete timeselector;


}

void CountDownTimer::on_btnReset_clicked()
{
    setTimerInterval(0);
    timerIntervalAtStart = 0;
    ui->lblTime->setText(QTime(0,0,0).addMSecs(getTimerInterval()).toString("HH:mm:ss:zzz"));
}

void CountDownTimer::on_view1000parts_clicked(bool checked)
{
    QString timeFormat = "HH:mm:ss";
    if(checked){
        timeFormat = "HH:mm:ss:zzz";
    }

    ui->lblTime->setText(QTime(0,0,0).addMSecs(getTimerInterval()).toString(timeFormat));
}

void CountDownTimer::on_cbJBEffekt_clicked()
{

}

void CountDownTimer::on_btnSetalarm_clicked()
{
    alarmselector mAlarmselector;
    mAlarmselector.exec();
}
