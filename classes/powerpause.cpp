#include "powerpause.h"

PowerPause::PowerPause(QObject *parent) : QObject(parent)
{

}

QString PowerPause::title() const
{
    return _title;
}

void PowerPause::setTitle(const QString &title)
{
    _title = title;
}

QImage PowerPause::image() const
{
    return _image;
}

void PowerPause::setImage(const QImage &image)
{
    _image = image;
}

QString PowerPause::helptext() const
{
    return _helptext;
}

void PowerPause::setHelptext(const QString &helptext)
{
    _helptext = helptext;
}

bool PowerPause::isActive() const
{
    return _isActive;
}

void PowerPause::setIsActive(bool isActive)
{
    _isActive = isActive;
}
