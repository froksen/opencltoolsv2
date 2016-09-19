#include "timeselector.h"
#include "ui_timeselector.h"
#include <QTime>
#include <QTimeEdit>
#include <QDebug>

TimeSelector::TimeSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSelector)
{
    ui->setupUi(this);

    ui->sbMinuts->setFocus();
}

TimeSelector::~TimeSelector()
{
    delete ui;
}

QTime TimeSelector::getTime()
{
    int hours = ui->sbHours->value();
    int minuts = ui->sbMinuts->value();
    int secs = ui->sbSecs->value();

    return QTime(hours,minuts,secs,0);
}

void TimeSelector::setTime(QTime time)
{
    ui->sbHours->setValue(time.hour());
    ui->sbMinuts->setValue(time.minute());
    ui->sbSecs->setValue(time.second());
}

void TimeSelector::setTime(int time_ms)
{
    QTime time = QTime(0,0,0,0).addMSecs(time_ms);

    setTime(time);
}

void TimeSelector::on_buttonBox_accepted()
{
}

void TimeSelector::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text() == "Reset"){
        ui->sbHours->setValue(0);
        ui->sbMinuts->setValue(0);
        ui->sbSecs->setValue(0);
    }

}
