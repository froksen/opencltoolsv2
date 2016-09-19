#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>;

Database::Database(QObject *parent) : QObject(parent)
{
    setDb(QSqlDatabase::addDatabase("QSQLITE"));
    getDb().setDatabaseName("db.sqlite");
}

bool Database::connect()
{
    //Åbner DB
    if(!getDb().open()){
        qDebug() << "Failed to open database";
        qDebug() << getDb().lastError().text();
        return false;
    }

    qDebug() << "Successfully opened database";
    return true;
}

QSqlTableModel *Database::selectTable(QString tableName, QString createTableQry)
{
    //Gemmer navnet
    setTableName(tableName);

    //Hvis ikke DB er åben, da åbnes den
    if(!getDb().isOpen()){
        connect();
    }

    //Laver objektet
    QSqlTableModel *model = new QSqlTableModel(this);

    //Undersøger om tabellen findes i db
    if(!createTableQry.isEmpty()){
        if(!getDb().tables().contains(tableName)){
            QSqlQuery query;
            if(!query.exec(createTableQry)){
                qDebug() << "Failed to create table" << tableName << query.lastError();
                return model;
            }

            qDebug() << "Successfully created table" << tableName;
        }
    }

    //Vælger tabellen, og retunerer den.
    model->setTable(tableName);
    if(!model->select()){
        qDebug() << "Failed to select table" << tableName;
    }

    return model;
}


bool Database::isOpen()
{
    return getDb().isOpen();
}

QSqlTableModel *Database::refreshTable()
{
    return selectTable(getTableName());
}


QSqlDatabase Database::getDb() const
{
    return db;
}

void Database::setDb(QSqlDatabase value)
{
    db = value;
}

QString Database::getTableName() const
{
    return _tableName;
}

void Database::setTableName(const QString &tableName)
{
    _tableName = tableName;
}

bool Database::execQry(QString qry)
{
    QSqlQuery query;
    if(!query.exec(qry)){
        qDebug() << "Failed to execute query:" << qry << "Error:" << query.lastError();
        return false;
    }

    qDebug() << "Successfully executed query:" << qry;
    return true;
}

