#include "powerpauseviewer.h"
#include "ui_powerpauseviewer.h"

PowerPauseViewer::PowerPauseViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerPauseViewer)
{
    ui->setupUi(this);
}

PowerPauseViewer::~PowerPauseViewer()
{
    delete ui;
}
