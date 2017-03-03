#include "randomnumber.h"
#include <QtCore>

RandomNumber::RandomNumber()
{
    setLower(0);
    setUpper(1);
    setAllowSameOutcomeTwice(false);
}

int RandomNumber::getRandomValue(bool simulate)
{
    if(!isValid()){
        return -9999;
    }

    //Sikre, at hvis listen er tom, da startes der forfra.
    if(getAvailableOutComes().count()<=0){
        updateAvailableOutComes();
    }

    //Vælger et tilfældigt tal i listen
    int pos = qrand() % ((getAvailableOutComes().count()) - 0) + 0;
    int number = getAvailableOutComes().at(pos);

    //Fjerner så det ikke kan vælges igen, hvis indstilingen er sat
    if(!allowSameOutcome && !simulate){
        QList<int> list = getAvailableOutComes();
        list.removeAt(pos);
        setAvailableOutComes(list);
        qDebug() <<getAvailableOutComes();
    }

    //Retunerer tallet
    return number;
}

int RandomNumber::getLower() const
{
    return lower;
}

void RandomNumber::setLower(int value)
{
    lower = value;
    qDebug() << "RandomNumber - Lower set to:" << value;
    if(isValid()){
        updateAvailableOutComes();
    }}

int RandomNumber::getUpper() const
{
    return upper;
}

void RandomNumber::setUpper(int value)
{
    qDebug() << "RandomNumber - Upper set to:" << value;
    upper = value;
    if(isValid()){
        updateAvailableOutComes();
    }
}

bool RandomNumber::allowSameOutcomeTwice()
{
    return allowSameOutcome;
}

void RandomNumber::setAllowSameOutcomeTwice(bool state)
{
    allowSameOutcome = state;
}

bool RandomNumber::isValid()
{
    if(getLower()<getUpper()){
        return true;
    }

    return false;
}

int RandomNumber::getPreviousRandomValue() const
{
    return previousRandomValue;
}

void RandomNumber::setPreviousRandomValue(int value)
{
    previousRandomValue = value;
}

int RandomNumber::pickRandomNumber()
{
    return qrand() % ((getUpper() + 1) - getLower()) + getLower();
}

QList<int> RandomNumber::getAvailableOutComes() const
{
    return _availableOutComes;
}

void RandomNumber::setAvailableOutComes(const QList<int> &availableOutComes)
{
    _availableOutComes = availableOutComes;
}

void RandomNumber::updateAvailableOutComes()
{
    QList<int> outcomes;
    //Sikre, at upper er større en lower
    if(isValid()){
        //Tilføjer de mulige udfald til listen
        for(int i=getLower();i<=getUpper();i++){
            outcomes.append(i);
        }
    }


    qDebug() << outcomes;
    //Sætter de nye muligheder
    setAvailableOutComes(outcomes);
}
