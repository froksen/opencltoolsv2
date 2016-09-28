#include "clock.h"
#include "ui_clock.h"
#include <QTimer>
#include <QTime>

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

    QString text = time.toString("hh:mm:ss");
    if(!ui->showSeconds->isChecked()){
        text = time.toString("hh:mm");
    }
//    if ((time.second() % 2) == 0)
//        text[2] = ' ';

    ui->time->setText(text);
}

void Clock::resizeEvent(QResizeEvent *)
{
    QFont font;
    font.setPixelSize(this->width()/10);
    ui->time->setFont(font);
}
