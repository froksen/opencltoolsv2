#include "spinboard.h"
#include "ui_spinboard.h"
#include <QPainter>
#include <QDebug>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

SpinBoard::SpinBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinBoard)
{
    ui->setupUi(this);
    repaint();

    setMinimumHeight(400);
    setMinimumWidth(400);

    //Sætter Scenen
    setScene(new QGraphicsScene(this));
    ui->graphicsView->setScene(getScene());

    blinkTimer = new QTimer(this);

    blinkTimer->setInterval(1000);

    connect(blinkTimer,SIGNAL(timeout()),this,SLOT(blinkTimerTimeOut()));

    //Tilføjer mulighederne for BOARDET
    //ui->cbBoardSize->addItem(QString("CL Teamplade"),4);
    for(int i=6;i>=2;i--){
         ui->cbBoardSize->addItem(QString("%1 felter").arg(i),i);
    }

    ui->allowSameOutcome->setChecked(true);
}

SpinBoard::~SpinBoard()
{
    delete ui;
}


void SpinBoard::drawSections(QPointF centrumOnBoard, float circleRadius, int numOfFields)
{
    QPainter painter(this);

     //TEGNER LINJERNE

     for(int i=1;i<=numOfFields;i++){
         //Finder vinklen til linjen.
         int anglePart = 360/numOfFields;
         int angle = anglePart * i;


         //Linjen
         QPointF lineStart(centrumOnBoard.x(),centrumOnBoard.y());
         QPointF lineEnd(centrumOnBoard.x()-circleRadius,centrumOnBoard.y());
         QLineF line(lineStart,lineEnd);

//         //Forrige linje - bruges til teksten
         QPointF lineNumStart(centrumOnBoard.x(),centrumOnBoard.y());
         QPointF lineNumEnd(centrumOnBoard.x()-circleRadius*0.7,centrumOnBoard.y());
         QLineF lineNum(lineNumStart,lineNumEnd);

         //Sætter den rigtige vinkel
         line.setAngle(angle);
         lineNum.setAngle(angle+(anglePart/2));


         //PEN
          QPen pen(Qt::black);
          painter.setPen(pen);

         //Tegner linjen
         painter.drawLine(line);

         //Tegner teksterne/tallene
         painter.setPen(QPen(Qt::transparent));
         painter.drawLine(lineNum); //Bruges til at bestemme, hvor tallet skal stå.


         QFont font = painter.font();
         font.setPixelSize(48);
         painter.setFont(font);

         painter.setPen(QPen(Qt::black));
         painter.drawText(lineNum.p2(),QString::number(i));

    }
}

QGraphicsScene *SpinBoard::getScene() const
{
    return scene;
}

void SpinBoard::setScene(QGraphicsScene *value)
{
    scene = value;
}

void SpinBoard::paintEvent(QPaintEvent *event)
{
    setScene(new QGraphicsScene(this));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setScene(getScene());
    ui->graphicsView->fitInView(getScene()->sceneRect(),Qt::KeepAspectRatio);

    getScene()->setBackgroundBrush(QBrush(Qt::darkGreen));

        float pWidth = ui->widget->width()*0.9;
        float pHeight = ui->widget->height()*0.9;

        float circleRadius;
        if(pWidth>pHeight){
            circleRadius = pHeight;
        }
        else {
            circleRadius = pWidth;
        }


    QGraphicsEllipseItem *board = getScene()->addEllipse(0,0,circleRadius,circleRadius,QPen(Qt::black),QBrush(Qt::white));

    if(ui->cbBoardSize->currentIndex() == 0){
        //getScene()->addPixmap(QPixmap(":/img/CL_Teamplade.png").scaled(circleRadius,circleRadius,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        //board->setVisible(false);
    }

    //TEGNER LINJERNE
    int numOfFields = ui->cbBoardSize->currentData().toInt();
    bool clTeamplate = false;

//    if(numOfFields==-1){
//        clTeamplate = true;
//        numOfFields = 4;
//    }

    for(int i=1;i<=numOfFields;i++){
        //Finder vinklen til linjen.
        int anglePart = 360/numOfFields;
        int angle = anglePart * i;


        //Linjen
        QPointF lineStart(board->rect().center().x(),board->rect().center().y());
        QPointF lineEnd(circleRadius,0);
        QLineF line(lineStart,lineEnd);
        line.setLength(circleRadius/2);

//         //Forrige linje - bruges til teksten
        QPointF lineNumStart(board->rect().center().x(),board->rect().center().y());
        QPointF lineNumEnd(-circleRadius*0.7,0);
        QLineF lineNum(lineNumStart,lineNumEnd);
        lineNum.setLength(circleRadius*0.3);

        //Sætter den rigtige vinkel
        line.setAngle(angle);
        lineNum.setAngle(angle+(anglePart/2));



        //PEN
         QPen pen(Qt::black);
         //painter.setPen(pen);

        //Tegner linjen
        //painter.drawLine(line);
         //if(ui->cbBoardSize->currentIndex() != 0){
             getScene()->addLine(line);
             getScene()->addLine(lineNum,QPen(Qt::transparent));
        //}

         if(!blinkTimer->isActive()){
             if(chosenNumber == i){
                 QGraphicsEllipseItem *SelectorBullet = getScene()->addEllipse(lineNum.p2().x()-16,lineNum.p2().y()-16,38,38,QPen(Qt::black),QBrush(Qt::red));
             }
         }
         else {
             if(i == chosingNumber_){
                 QGraphicsEllipseItem *SelectorBullet = getScene()->addEllipse(lineNum.p2().x()-16,lineNum.p2().y()-16,38,38,QPen(Qt::black),QBrush(Qt::yellow));
             }
         }


         //if(ui->cbBoardSize->currentIndex() != 0){
             QFont txtFont; //= new QFont();
             txtFont.setPixelSize(48);

             QGraphicsTextItem *txt = getScene()->addText(QString::number(i));
             txt->setFont(txtFont);
             txt->setX(lineNum.p2().x());
             txt->setY(lineNum.p2().y()-txtFont.pixelSize());
         //}

    }
}

void SpinBoard::on_btnSpin_clicked()
{
    //Vælger udfaldet!
    chosenNumber = rndChosenNumber.getRandomValue();

    chosingNumber.setLower(rndChosenNumber.getLower());
    chosingNumber.setUpper(rndChosenNumber.getUpper());
    chosingNumber.setAllowSameOutcomeTwice(true);

    numberOfBlinks = 20;

    blinkTimer->start(250);

    ui->btnSpin->setDisabled(blinkTimer->isActive());
    ui->cbBoardSize->setDisabled(blinkTimer->isActive());
}

void SpinBoard::blinkTimerTimeOut()
{
    chosingNumber_ = chosingNumber.getRandomValue(true);

    if(numberOfBlinks--<=0){
        blinkTimer->stop();
        qDebug() << "blinkTimer stopped";
        ui->btnSpin->setDisabled(blinkTimer->isActive());
        ui->cbBoardSize->setDisabled(blinkTimer->isActive());

    }


    repaint();
}

void SpinBoard::on_cbBoardSize_currentIndexChanged(int index)
{
    rndChosenNumber.setUpper(ui->cbBoardSize->currentData().toInt());
    rndChosenNumber.setLower(1);
}

void SpinBoard::on_allowSameOutcome_clicked(bool checked)
{
    rndChosenNumber.setAllowSameOutcomeTwice(checked);
}
