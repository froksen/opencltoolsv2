#include "alarmselector.h"
#include "ui_alarmselector.h"

alarmselector::alarmselector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarmselector)
{
    ui->setupUi(this);
}

alarmselector::~alarmselector()
{
    delete ui;
}
