#include "alarmselector.h"
#include "ui_alarmselector.h"
#include <QTime>
#include <QDebug>
#include <QPushButton>
#include <QTimer>

alarmselector::alarmselector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarmselector)
{
    ui->setupUi(this);
    QTime time;
    ui->sbHours->setValue(time.currentTime().hour());
    ui->sbMinuts->setValue(time.currentTime().minute());
    ui->sbSecs->setValue(time.currentTime().second());

    //Timer som validere det valgte klokkeslæt hvert sekund
    QTimer *validateTimer = new QTimer(this);
    connect(validateTimer,SIGNAL(timeout()),this,SLOT(validateTime()));
    validateTimer->setInterval(1000);
    validateTimer->start();
}

alarmselector::~alarmselector()
{
    delete ui;
}

void alarmselector::on_sbHours_valueChanged(int arg1)
{
    validateTime();
}

bool alarmselector::beforeCurrentTime()
{
    int hours = ui->sbHours->value();
    int minuts = ui->sbMinuts->value();
    int seconds = ui->sbSecs->value();
    int timeInMillis = hours*60*60*1000 + minuts*60*1000 + seconds*1000;
    qDebug() << "timeInMillis" << timeInMillis << "currentMillis" << QTime::currentTime().msecsSinceStartOfDay();

    if(QTime::currentTime().msecsSinceStartOfDay()>timeInMillis)
    {
        qDebug() << "Tidspunktet er sat før nurværrende tidspunkt: " << QTime::currentTime().toString();
        return false;
    }
    return true;
}

void alarmselector::on_sbMinuts_valueChanged(int arg1)
{
    validateTime();
}

void alarmselector::on_sbSecs_valueChanged(int arg1)
{
    validateTime();
}

void alarmselector::validateTime()
{
    ui->lblNotice->setVisible(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    if(beforeCurrentTime())
    {
        ui->lblNotice->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
