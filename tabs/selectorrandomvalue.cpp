#include "selectorrandomvalue.h"
#include "ui_selectorrandomvalue.h"



SelectorRandomValue::SelectorRandomValue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorRandomValue)
{
    ui->setupUi(this);


    setRandomNumberFrom(0);
    setRandomNumberTo(10);
    ui->sbNumberFrom->setValue(0);
    ui->sbNumberTo->setValue(10);

    QString style = "QSpinBox::up-button { width: 32px; }"
                    "QSpinBox::down-button { width: 32px; }";

    ui->sbNumberFrom->setStyleSheet(style);
    ui->sbNumberTo->setStyleSheet(style);


    animationShade = new AnimationShade(this);
    connect(ui->btnNewNumber,SIGNAL(clicked(bool)),animationShade,SLOT(runAnimation()));
    connect(ui->cbShowAnimationShade,SIGNAL(clicked(bool)),animationShade,SLOT(showShade(bool)));
}

SelectorRandomValue::~SelectorRandomValue()
{
    delete ui;
}

void SelectorRandomValue::on_sbNumberFrom_valueChanged(int arg1)
{
    setRandomNumberFrom(arg1);

    if(rnd.isValid()){
        ui->btnNewNumber->setEnabled(true);
    }
    else {
        ui->btnNewNumber->setEnabled(false);
    }
}

int SelectorRandomValue::getRandomNumberFrom() const
{
    return randomNumberFrom;
}

void SelectorRandomValue::setRandomNumberFrom(int value)
{
    randomNumberFrom = value;
    rnd.setLower(getRandomNumberFrom());
}

int SelectorRandomValue::getRandomNumberTo() const
{
    return randomNumberTo;
}

void SelectorRandomValue::setRandomNumberTo(int value)
{
    randomNumberTo = value;
        rnd.setUpper(getRandomNumberTo());
}

void SelectorRandomValue::pickRandomNumber()
{

    ui->lblNumber->setText(QString::number(rnd.getRandomValue()));
}

void SelectorRandomValue::on_sbNumberTo_valueChanged(int arg1)
{
    setRandomNumberTo(arg1);

    if(rnd.isValid()){
        ui->btnNewNumber->setEnabled(true);
    }
    else {
        ui->btnNewNumber->setEnabled(false);
    }
}

void SelectorRandomValue::on_btnNewNumber_clicked()
{
    pickRandomNumber();
}

void SelectorRandomValue::on_cbAllowSameOutcomeTwice_clicked(bool checked)
{
    rnd.setAllowSameOutcomeTwice(checked);
}

void SelectorRandomValue::resizeEvent(QResizeEvent *)
{
    //Tilpasser teksten
    QFont font;
    font.setPixelSize(this->width()/5);
    ui->lblNumber->setFont(font);
}
