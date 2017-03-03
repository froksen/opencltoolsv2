#include "selectorfinger.h"
#include "ui_selectorfinger.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "classes/randomnumber.h"

SelectorFinger::SelectorFinger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorFinger)
{
    ui->setupUi(this);

    //Det første billede brugeren ser.
//    selectedPixmap = getFingerImage(-1);
//    ui->labelFinger->setPixmap(selectedPixmap);
//    ui->labelFinger->setPixmap(selectedPixmap.scaled(ui->labelFinger->width()-100,ui->labelFinger->height()-100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//    //ui->labelFinger2->setPixmap(selectedPixmap.scaled(ui->labelFinger2->width()-100,ui->labelFinger->height()-100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->lblNumber->clear();
    ui->labelFinger->clear();
    ui->labelFinger2->clear();
    ui->lblNumber->setText("?");
    on_cbShowNumber_clicked(false);

    //Timer som bruges til, når resultatet ikke skal vises direkte
    animationTimer = new QTimer(this);
    animationTimer->setInterval(100);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(on_animationtimer_timeout()));
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(toogleGuiEnables()));
    connect(ui->btnNewOutcome,SIGNAL(clicked(bool)),this,SLOT(toogleGuiEnables()));

    //Sætter pointer til et klassen
    _mRandomNumber = new RandomNumber();
}

SelectorFinger::~SelectorFinger()
{
    delete ui;
}

int SelectorFinger::getRandomNumberBetween(int low, int high)
{
    qDebug() << high;
    RandomNumber rnd;// = new RandomNumber(this);
    rnd.setLower(low);
    rnd.setUpper(high);
    return rnd.getRandomValue();
}

void SelectorFinger::on_btnNewOutcome_clicked()
{
    //Sætter intervallet
    getMRandomNumber()->setUpper(10);
    getMRandomNumber()->setLower(1);

    //Tillad 0?
    if(ui->cbAllowZero->isChecked()){
        getMRandomNumber()->setLower(0);
    }

    //Tillad samme udfald flere gange?
    getMRandomNumber()->setAllowSameOutcomeTwice(true);

    //Vis resultatet med det samme?
    if(ui->cbShowInstant->isChecked()){
        showResult();
        return;
    }

    //Starter animationen;
    animationTimerAttemts = 25;
    animationTimer->start();
}

void SelectorFinger::resizeEvent(QResizeEvent *)
{
//    int width = ui->labelFinger->width()-100;
//    int height = ui->labelFinger->height()-100;
//    int x = ui->labelFinger->x();
//    int y = ui->labelFinger->y();

//    ui->labelFinger->setPixmap(ui->labelFinger->pixmap()->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//    ui->labelFinger2->setPixmap(ui->labelFinger2->pixmap()->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    if(ui->lblNumber->text() != "?"){
       setFingerNumber(ui->lblNumber->text().toInt(),true);
    }


}

QPixmap SelectorFinger::getFingerImage(int finger)
{
    if(finger>5 || finger < 1){
        qDebug() << "Du skal vælge en finger mellem 0 - 5";
    }
    //Hvilket finger-billede der skal vises.
    QString fingerUrl;
    switch(finger){
    case 0:
        fingerUrl = ":/img/fingerZero.png";
        break;
    case 1:
        fingerUrl = ":/img/fingerOne.png";
        break;
    case 2:
        fingerUrl = ":/img/fingerTwo.png";
        break;
    case 3:
        fingerUrl = ":/img/fingerThree.png";
        break;
    case 4:
        fingerUrl = ":/img/fingerFour.png";
        break;
    case 5:
        fingerUrl = ":/img/fingerFive.png";
        break;
    default:
        fingerUrl = ":/img/fingerAll.jpg";
    }

    return QPixmap(fingerUrl);
}

void SelectorFinger::setFingerNumber(int number,bool showBothHands)
{
    ui->labelFinger2->setVisible(showBothHands);

    QString finger1;
    QString finger2;

    switch(number){
    case -1:
        finger1 = ":/img/Questionmark.png";
        finger2 = ":/img/Questionmark.png";
        break;
    case 0:
        finger1 = ":/img/fingerZero.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 1:
        finger1 = ":/img/fingerOne.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 2:
        finger1 = ":/img/fingerTwo.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 3:
        finger1 = ":/img/fingerThree.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 4:
        finger1 = ":/img/fingerFour.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 5:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerZero.png";
        break;
    case 6:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerOne.png";
        break;
    case 7:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerTwo.png";
        break;
    case 8:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerThree.png";
        break;
    case 9:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerFour.png";
        break;
    case 10:
        finger1 = ":/img/fingerFive.png";
        finger2 = ":/img/fingerFive.png";
        break;
    default:
        break;
    }

    QImage hand1(finger1);
    QImage hand2(finger2);
    hand2 = hand2.mirrored(true,false);

    if(ui->cbMirrorHands->isChecked()){
        hand2 = QImage(finger1);
        hand1 = QImage(finger2).mirrored(true,false);
    }

    int width = ui->labelFinger->width()-100;
    int height = ui->labelFinger->height()-100;
    ui->lblNumber->setText(QString::number(number));
    ui->labelFinger->setPixmap(QPixmap::fromImage(hand1).scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->labelFinger2->setPixmap(QPixmap::fromImage(hand2).scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

void SelectorFinger::on_cbShowNumber_clicked(bool checked)
{
    ui->lblNumber->setVisible(checked);
}

void SelectorFinger::on_cbShowInstant_clicked(bool checked)
{

}

void SelectorFinger::on_animationtimer_timeout()
{
    if(--animationTimerAttemts <= 0)
    {
        animationTimer->stop();
    }
    showResult();
//    if(animationTimerAttemts<25){
//        qDebug() << "Animation timer attempt " << animationTimerAttemts << "of" << 50;
//        showResult();
//        animationTimerAttemts++;
//    }
//    else {
//        animationTimer->stop();
//        qDebug() << "Animation timer stopped";
//        animationTimerAttemts = 0;
//    }

}

void SelectorFinger::showResult()
{
    int rndNum;
    if(ui->cbAllowZero->isChecked()){
        rndNum = getRandomNumberBetween(0,10);
    }
    else {
        rndNum = getRandomNumberBetween(1,10);
    }

    if(rndNum == ui->lblNumber->text().toInt()){
        showResult();
        return;
    }

    setFingerNumber(rndNum,true);
}

RandomNumber *SelectorFinger::getMRandomNumber() const
{
    return _mRandomNumber;
}

void SelectorFinger::toogleGuiEnables()
{
    ui->cbAllowZero->setEnabled(true);
    ui->cbShowInstant->setEnabled(true);
    ui->cbShowNumber->setEnabled(true);
    ui->btnNewOutcome->setEnabled(true);
    ui->cbMirrorHands->setEnabled(true);

    if(animationTimer->isActive()){
        ui->cbAllowZero->setEnabled(false);
        ui->cbShowInstant->setEnabled(false);
        ui->cbShowNumber->setEnabled(false);

        ui->btnNewOutcome->setEnabled(false);
        ui->cbMirrorHands->setEnabled(false);
    }
}

void SelectorFinger::on_cbMirrorHands_clicked()
{
    bool isNum;
    int num = ui->lblNumber->text().toInt(&isNum);
    if(!isNum){
        num = -1;
    }

    setFingerNumber(num,true);
}
