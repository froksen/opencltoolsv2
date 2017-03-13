#ifndef SELECTORRANDOMVALUE_H
#define SELECTORRANDOMVALUE_H

#include <QWidget>
#include "classes/randomnumber.h"
#include "classes/animationshade.h"

namespace Ui {
class SelectorRandomValue;
}

class SelectorRandomValue : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorRandomValue(QWidget *parent = 0);
    ~SelectorRandomValue();

private slots:
    void on_sbNumberFrom_valueChanged(int arg1);
    void on_sbNumberTo_valueChanged(int arg1);
    void on_btnNewNumber_clicked();
    void on_cbAllowSameOutcomeTwice_clicked(bool checked);

    void on_excludeOutcomeButton_clicked();

private:
    Ui::SelectorRandomValue *ui;

    void resizeEvent(QResizeEvent*);

    int getRandomNumberFrom() const;
    void setRandomNumberFrom(int value);

    int getRandomNumberTo() const;
    void setRandomNumberTo(int value);

    void pickRandomNumber();

    int randomNumberFrom;
    int randomNumberTo;

    QStringList previousNumbers;

    RandomNumber rnd;

    AnimationShade *animationShade;
};

#endif // SELECTORRANDOMVALUE_H
