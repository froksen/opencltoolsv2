#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H
#include <QList>


class RandomNumber
{
public:
    RandomNumber();

    int getRandomValue(bool simulate = false);

    int getLower() const;
    void setLower(int value);

    int getUpper() const;
    void setUpper(int value);
    void setAllowSameOutcomeTwice(bool state = true);
    bool allowSameOutcomeTwice();
    bool isValid();
    void setExcludeOutComes(const QList<int> &excludeOutComes);
    QList<int> getExcludeOutComes() const;


private:
    int getPreviousRandomValue() const;
    void setPreviousRandomValue(int value);
    int pickRandomNumber();
    QList<int> getAvailableOutComes() const;
    void setAvailableOutComes(const QList<int> &availableOutComes);
    void updateAvailableOutComes();

    int lower;
    int upper;
    int previousRandomValue;
    bool allowSameOutcome;
    QList<int> _availableOutComes;
    QList<int> _excludeOutComes;
};




#endif // RANDOMNUMBER_H
