#ifndef SPINBOARD_H
#define SPINBOARD_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QTimer>
#include "classes/randomnumber.h"

namespace Ui {
class SpinBoard;
}

class SpinBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SpinBoard(QWidget *parent = 0);
    ~SpinBoard();

private:
    Ui::SpinBoard *ui;

    void drawSections(QPointF centrumOnBoard,float circleRadius,int numOfFields);

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *value);

    QGraphicsScene *scene;

    QTimer *blinkTimer;
    int numberOfBlinks = 20;

    int chosenNumber;
    int chosingNumber_;
    RandomNumber rndChosenNumber;
    RandomNumber chosingNumber;


protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_btnSpin_clicked();
    void blinkTimerTimeOut();
    void on_cbBoardSize_currentIndexChanged(int index);
    void on_allowSameOutcome_clicked(bool checked);
};

#endif // SPINBOARD_H
