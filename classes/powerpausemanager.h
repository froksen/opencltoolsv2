#ifndef POWERPAUSEMANAGER_H
#define POWERPAUSEMANAGER_H

#include <QObject>
#include <QList>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "classes/powerpause.h"
#include "classes/database.h"

class PowerPauseManager : public QObject
{
    Q_OBJECT
public:
    explicit PowerPauseManager(QObject *parent = 0);

    bool loadAll();
    bool loadAll(bool isActive);
    bool load(int id);
    bool remove(int id);
    bool append(QString title, QString helpText, QByteArray image); //
    bool append(QString title, QString helpText, QPixmap image);
    bool save();
    QList<PowerPause *> *getItems() const;
    QSqlTableModel *getItemsModel() const;

private:
    Database *database() const;
    QSqlTableModel *getModel() const;

    //Voids
    bool getFromDatabase();
    QString htmlHelpText(QString materialer, QString instruktion, QString variation, QString fraUrl);

    //Variables
    QList<PowerPause *> *_items;

    QSqlTableModel *_model;
    Database *_database;


signals:

public slots:
};

#endif // POWERPAUSEMANAGER_H
