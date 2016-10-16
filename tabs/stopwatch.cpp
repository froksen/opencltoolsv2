#include "stopwatch.h"
#include "ui_stopwatch.h"
#include <QDebug>
#include <QTime>

StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StopWatch)
{
    ui->setupUi(this);

    QTimer *tickTimer = new QTimer(this);
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(updateTimer()));
    tickTimer->setInterval(100);
    setTickTimer(tickTimer);

    setTime(0);
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
    QString text = QTime(0,0,0).addMSecs(time()).toString(timeFormat());
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

quint64 StopWatch::time() const
{
    return _time;
}

void StopWatch::setTime(const quint64 &time)
{
    _time = time;
}

void StopWatch::updateFormat()
{
    QString formatText;
   //Timer
    if(ui->showHours->isChecked())
    {
        formatText.append("HH:");
    }

    //Minutter
    if(ui->showMinuts->isChecked())
    {
        formatText.append("mm:");
    }


    //Sekunder
    formatText.append("ss");

    //Sætter det nye format
    setTimeFormat(formatText);
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
