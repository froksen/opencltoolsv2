#ifndef PERSONINFORMATION_H
#define PERSONINFORMATION_H

#include <QObject>

class PersonInformation : public QObject
{
    Q_OBJECT
public:
    explicit PersonInformation(QObject *parent = 0);

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

signals:

public slots:

private:

    int id;
    QString name;


};

#endif // PERSONINFORMATION_H
