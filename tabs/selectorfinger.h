#ifndef SELECTORFINGER_H
#define SELECTORFINGER_H

#include <QWidget>
#include <QPixmap>
#include "classes/randomnumber.h"

namespace Ui {
class SelectorFinger;
}

class SelectorFinger : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorFinger(QWidget *parent = 0);
    ~SelectorFinger();


private slots:
    void on_btnNewOutcome_clicked();
    void on_cbShowNumber_clicked(bool checked);
    void on_cbShowInstant_clicked(bool checked);
    void on_animationtimer_timeout();
    void toogleGuiEnables();
    void on_cbMirrorHands_clicked();

private:
    Ui::SelectorFinger *ui;
    void resizeEvent(QResizeEvent*);
    QPixmap getFingerImage(int finger);
    void setFingerNumber(int number = -1, bool showBothHands = false);
    int getRandomNumberBetween(int low, int high);
    void showResult();

    RandomNumber *getMRandomNumber() const;


    QPixmap selectedPixmap;
    int randomNumber;

    RandomNumber *_mRandomNumber;


    QTimer *animationTimer;
    int animationTimerAttemts;
};

#endif // SELECTORFINGER_H
