#include "selectorrandomvalue.h"
#include "ui_selectorrandomvalue.h"
#include <QInputDialog>
#include <QDebug>

SelectorRandomValue::SelectorRandomValue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorRandomValue)
{
    ui->setupUi(this);


//    setRandomNumberFrom(0);
//    setRandomNumberTo(10);
    ui->sbNumberFrom->setValue(0);
    ui->sbNumberTo->setValue(10);
    on_sbNumberFrom_valueChanged(0);
    on_sbNumberTo_valueChanged(10);

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
    previousNumbers.clear();
    ui->previousNumbers->setText("");
    rnd.setLower(getRandomNumberFrom());
}

int SelectorRandomValue::getRandomNumberTo() const
{
    return randomNumberTo;
}

void SelectorRandomValue::setRandomNumberTo(int value)
{
    randomNumberTo = value;
    previousNumbers.clear();
    ui->previousNumbers->setText("");
    rnd.setUpper(getRandomNumberTo());
}

void SelectorRandomValue::pickRandomNumber()
{

    ui->lblNumber->setText(QString::number(rnd.getRandomValue()));

    previousNumbers.append(ui->lblNumber->text());

    if(previousNumbers.count()>15){
        previousNumbers.removeFirst();
    }

    QString preTx = "";
    foreach(QString txt, previousNumbers){
        preTx.append(txt).append(" ");
    }

    ui->previousNumbers->setText(preTx);

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

void SelectorRandomValue::on_excludeOutcomeButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Udeluk udfald"),
                                         tr("Skriv hvilke tal du vil udelukke. Skriv tallene adskildt med semikolon (1;3;4)"), QLineEdit::Normal,
                                         "", &ok);

    if(ok)
    {
        QList<int> excludeList;
        foreach(QString number, text.split(";"))
        {
            bool isNumber;
            int intNumber = number.toInt(&isNumber);

            if(isNumber)
            {
                  excludeList.append(intNumber);
            }
        }
        qDebug() << "Excluding " << excludeList;
        rnd.setExcludeOutComes(excludeList);
    }
}
