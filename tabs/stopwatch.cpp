#include "stopwatch.h"
#include "ui_stopwatch.h"

StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StopWatch)
{
    ui->setupUi(this);
}

StopWatch::~StopWatch()
{
    delete ui;
}
