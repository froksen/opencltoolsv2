#ifndef POWERPAUSE_H
#define POWERPAUSE_H

#include <QObject>
#include <QImage>

class PowerPause : public QObject
{
    Q_OBJECT
public:
    explicit PowerPause(QObject *parent = 0);

    QString title() const;
    void setTitle(const QString &title);

    QImage image() const;
    void setImage(const QImage &image);

    QString helptext() const;
    void setHelptext(const QString &helptext);

    bool isActive() const;
    void setIsActive(bool isActive);

private:
    QString _title;
    QString _helptext;
    QImage _image;
    bool _isActive;


signals:

public slots:
};

#endif // POWERPAUSE_H
