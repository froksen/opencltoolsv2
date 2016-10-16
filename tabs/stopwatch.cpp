#include "stopwatch.h"
#include "ui_stopwatch.h"
#include <QDebug>
#include <QTime>
#include <QFont>

StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StopWatch)
{
    ui->setupUi(this);

    QTimer *tickTimer = new QTimer(this);
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(updateTimer()));
    tickTimer->setInterval(1);
    setTickTimer(tickTimer);

    setTime(100);
    setTime(0);
    updateFormat();
    updateTimer();
}

StopWatch::~StopWatch()
{
    delete ui;
}

void StopWatch::updateTimer()
{
    //Lægger ny tid til
    if(tickTimer()->isActive()){
        quint64 nTime = time() + tickTimer()->interval();
        setTime(nTime);
    }

    qDebug() << "updateTimer";
    QTime timestamp = QTime(0,0,0).addMSecs(time());
    QString text = timestamp.toString(timeFormat());

    //Hvis der kun skal vises sekunder og minutter
    if(!ui->showHours->isChecked()){
        int msecs = QTime(0,0).msecsTo(timestamp);
        //int hours = msecs/(1000*60*60);
        int minutes = (msecs)/(1000*60);
        int seconds = (msecs-(minutes*1000*60))/1000;
        int milliseconds = msecs-(seconds*1000)-(minutes*1000*60);

        text = QString::number(minutes) + ":" + QString::number(seconds);
    }

    //Hvis der kun skal vises sekunder
    if(!ui->showHours->isChecked() && !ui->showMinuts->isChecked()){
        text = QString::number(QTime(0,0).secsTo(timestamp));
    }

   ui->time->setText(text);
}

QTimer *StopWatch::tickTimer() const
{
    return _tickTimer;
}

void StopWatch::setTickTimer(QTimer *tickTimer)
{
    _tickTimer = tickTimer;
}

void StopWatch::on_StartStopButton_clicked()
{
    if(tickTimer()->isActive()){
        tickTimer()->stop(); //Stopper timer
        return;
    }

    updateFormat(); //Opdaterer tidsformatet
    tickTimer()->start(); //Starter timer;
}

double StopWatch::time() const
{
    return _time;
}

void StopWatch::setTime(const double &time)
{
    _time = time;
}

void StopWatch::updateFormat()
{
    QString formatText;
    QString formatLabelText;
   //Timer
    if(ui->showHours->isChecked())
    {
        formatText.append("HH:");
        formatLabelText.append("Timer:");
    }

    //Minutter
    if(ui->showMinuts->isChecked())
    {
        formatText.append("mm:");
        formatLabelText.append("Minutter:");
    }


    //Sekunder
    formatText.append("ss");
    formatLabelText.append("Sekunder");


    //Sætter det nye format
    setTimeFormat(formatText);
    ui->formatLabel->setText(formatLabelText);
}

void StopWatch::resizeEvent(QResizeEvent *)
{
    //    //Tilpasser teksten
        QFont font;
        font.setPixelSize(this->width()/10);
        ui->time->setFont(font);

        font.setPixelSize(this->width()/50);
        ui->formatLabel->setFont(font);
}

QString StopWatch::timeFormat() const
{
    return _timeFormat;
}

void StopWatch::setTimeFormat(const QString &timeFormat)
{
    _timeFormat = timeFormat;
}

void StopWatch::on_ResetButton_clicked()
{
    setTime(0);
    updateTimer();
}

void StopWatch::on_showHours_clicked()
{
    updateFormat();
}

void StopWatch::on_showMinuts_clicked()
{
    updateFormat();
}
