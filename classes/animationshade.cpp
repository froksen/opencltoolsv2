#include "animationshade.h"
#include "ui_animationshade.h"
#include <QPalette>
#include <QTimer>

AnimationShade::AnimationShade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationShade)
{
    ui->setupUi(this);

    //Tekstfaven på label
    QPalette lblPal = ui->label->palette();
    lblPal.setColor(QPalette::Foreground,Qt::white);
    ui->label->setPalette(lblPal);

    //Sætter den første farve
    switchColor();

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->resize(parent->width(),parent->height());
    this->adjustSize();

    //Opsætning af timeren
    timer = new QTimer(this);
    timer->setInterval(250);

    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimeout()));

    setVisible(false);
}

AnimationShade::~AnimationShade()
{
    delete ui;
}

void AnimationShade::runAnimation()
{
    if(!showshade){
        return;
    }

    this->resize(parentWidget()->width(),parentWidget()->height());
    this->setVisible(true);
    blinkCount = 0;
    timer->start();
}

void AnimationShade::showShade(bool state)
{
    showshade = state;
}

void AnimationShade::timerTimeout()
{
    switchColor();
   this->resize(parentWidget()->width(),parentWidget()->height());
    if(++blinkCount>10){
        timer->stop();
        this->setVisible(false);
    }
}


void AnimationShade::switchColor()
{
    QColor color;

    if(bgWhite){
        color = QColor(Qt::gray);
        bgWhite = false;
    }
    else {
        color = QColor(Qt::white);
        bgWhite = true;
    }

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

