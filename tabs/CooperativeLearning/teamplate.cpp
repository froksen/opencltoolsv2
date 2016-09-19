#include "teamplate.h"
#include "ui_teamplate.h"
#include <QImage>
#include <QDebug>

TeamPlate::TeamPlate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamPlate)
{
    ui->setupUi(this);

    //Sætter pladen
    setTeamplatepixmap(QPixmap(":/img/CL_Teamplade.png"));
}

TeamPlate::~TeamPlate()
{
    delete ui;
}

QPixmap TeamPlate::teamplatepixmap() const
{
    return _teamplatepixmap;
}

void TeamPlate::setTeamplatepixmap(const QPixmap &teamplatepixmap)
{
    _teamplatepixmap = teamplatepixmap;
    scaleTeamplateToLabel();
}

void TeamPlate::scaleTeamplateToLabel()
{

    QPixmap scaledImg = teamplatepixmap();

    int w = ui->teamplate->width();
    int h = ui->teamplate->height();

    scaledImg = scaledImg.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->teamplate->setPixmap(scaledImg);
}

void TeamPlate::resizeEvent(QResizeEvent *)
{
    scaleTeamplateToLabel();
}
