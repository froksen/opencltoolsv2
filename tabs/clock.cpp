#include "clock.h"
#include "ui_clock.h"
#include <QTimer>
#include <QTime>
#include <QDate>

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    QTimer *mTimer = new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(showTime()));
    mTimer->start(1000);

    ui->setupUi(this);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::showTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    QString text = time.toString("hh:mm:ss");
    if(!ui->showSeconds->isChecked()){
        text = time.toString("hh:mm");
    }

    QString dateText = "";
    switch(date.dayOfWeek()){
        case 1:
            dateText.append("Mandag");
        break;
        case 2:
            dateText.append("Tirsdag");
        break;
        case 3:
            dateText.append("Onsdag");
        break;
        case 4:
            dateText.append("Torsdag");
        break;
        case 5:
            dateText.append("Fredag");
        break;
    case 6:
            dateText.append("Lørdag");
        break;
    case 7:
           dateText.append("Søndag");
        break;
    }
    dateText.append(" den ");
    dateText.append(date.toString("dd. MM. yyyy"));


//    if ((time.second() % 2) == 0)
//        text[2] = ' ';

    ui->time->setText(text);
    ui->dateLabel->setText(dateText);

    if(ui->showDate->isChecked()){
        ui->dateLabel->setHidden(false);
    }
    else {
        ui->dateLabel->setHidden(true);
    }
}

void Clock::resizeEvent(QResizeEvent *)
{
    QFont font;
    int pixelSize = (this->width()/5)/4;
    font.setPixelSize(pixelSize*4);

    if(ui->showDate->isChecked()){
        font.setPixelSize(pixelSize*1);
        ui->dateLabel->setFont(font);
        font.setPixelSize(pixelSize*3);
    }

    ui->time->setFont(font);

}

void Clock::on_showSeconds_toggled(bool checked)
{
    showTime();
}

void Clock::on_showDate_toggled(bool checked)
{
    showTime();
    this->resize(this->geometry().width()-1, this->geometry().height()-1);

}
