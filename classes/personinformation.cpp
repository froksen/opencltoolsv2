#include "personinformation.h"

PersonInformation::PersonInformation(QObject *parent) : QObject(parent)
{

}

QString PersonInformation::getName() const
{
    return name;
}

void PersonInformation::setName(const QString &value)
{
    name = value;
}

int PersonInformation::getId() const
{
    return id;
}

void PersonInformation::setId(int value)
{
    id = value;
}
