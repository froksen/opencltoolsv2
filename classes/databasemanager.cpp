#include "databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlQuery>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}

QString DatabaseManager::currentDatabaseFile() const
{
    return _currentDatabaseFile;
}

void DatabaseManager::setCurrentDatabaseFile(const QString &currentDatabaseFile)
{
    _currentDatabaseFile = currentDatabaseFile;
}

bool DatabaseManager::open()
{
    //Hvis der ikke er lavet en instence, da lav den
    if(!currentDatabase().isOpen()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("db.sqlite");
        setCurrentDatabase(db);
    }

    setSplashScreenText("Indlæser databasen");
    //Tjekker om den kunne åbnes.
    if(!currentDatabase().open()){
        qDebug() << "ERROR:" << currentDatabase().lastError().text();
        setSplashScreenText("Indlæsning af databasen mislykkes!");
        return false;
    }

    setSplashScreenText("Indlæsning af databasen lykkes!");
    return true;
}

void DatabaseManager::closeAndRemoveDatabase(QString connectionName)
{
    currentDatabase().close();
    QSqlDatabase::removeDatabase(connectionName);
}

QSqlDatabase DatabaseManager::currentDatabase() const
{
    return _currentDatabase;
}

void DatabaseManager::setCurrentDatabase(const QSqlDatabase &currentDatabase)
{
    _currentDatabase = currentDatabase;
}

QString DatabaseManager::splashScreenText() const
{
    return _splashScreenText;
}

void DatabaseManager::setSplashScreenText(const QString &splashScreenText)
{
    _splashScreenText = splashScreenText;
}


QSqlTableModel *DatabaseManager::selectedTable() const
{
    return _selectedTable;
}

void DatabaseManager::setSelectedTable(QSqlTableModel *selectedTable)
{
    _selectedTable = selectedTable;
}

QStringList DatabaseManager::execMultibleList() const
{
    return _execMultibleList;
}

void DatabaseManager::setExecMultibleList(const QStringList &execMultibleList)
{
    _execMultibleList = execMultibleList;
}

bool DatabaseManager::execMultible()
{
    foreach(QString qry,execMultibleList()){
        if(!exec(qry)) {
            setSplashScreenText(qry);
            return false;
        }
    }
    return true;
}



QString DatabaseManager::selectedTableName() const
{
    return _selectedTableName;
}

void DatabaseManager::setSelectedTableName(const QString &selectedTableName)
{
    _selectedTableName = selectedTableName;
}

QSqlTableModel *DatabaseManager::selectTable()
{
    setSelectedTable(new QSqlTableModel(this));

    selectedTable()->setTable(selectedTableName());

    if(!selectedTable()->select()){
        qDebug() << "Error on selecting table" << selectedTableName() << ":" << selectedTable()->lastError().text();
    }

    return selectedTable();
}

QSqlTableModel *DatabaseManager::selectTable(QString tableName)
{
    setSelectedTableName(tableName);
    return selectTable();
}

void DatabaseManager::refreshCurrentTable()
{
    selectedTable()->select();
}

bool DatabaseManager::exec(QString query)
{
    setSplashScreenText("Udfører database query...");
    QSqlQuery qry;
    if(!qry.exec(query)){
        qDebug() << "Failed to execute query:" << query << "Error:" << qry.lastError();
        return false;
    }

    return true;
}


QString DatabaseManager::currentTableName() const
{
    return _currentTableName;
}

void DatabaseManager::setCurrentTableName(const QString &currentTableName)
{
    _currentTableName = currentTableName;
}
