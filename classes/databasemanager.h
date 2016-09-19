#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QAbstractItemModel>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);



    QString currentTableName() const;
    void setCurrentTableName(const QString &currentTableName);

    QString currentDatabaseFile() const;
    void setCurrentDatabaseFile(const QString &currentDatabaseFile);

    bool open();
    QSqlDatabase currentDatabase() const;
    void setCurrentDatabase(const QSqlDatabase &currentDatabase);


    QString splashScreenText() const;

    QString selectedTableName() const;
    void setSelectedTableName(const QString &selectedTableName);

    QSqlTableModel *selectTable();
    QSqlTableModel *selectTable(QString tableName);
    void refreshCurrentTable();

public slots:

signals:

private:
    QString _currentTableName;
    QString _currentDatabaseFile;
    QSqlDatabase _currentDatabase;

    void setSplashScreenText(const QString &splashScreenText);
    QString _splashScreenText;

    QString _selectedTableName;

    QSqlTableModel *selectedTable() const;
    void setSelectedTable(QSqlTableModel *selectedTable);
    QSqlTableModel *_selectedTable;
};

#endif // DATABASEMANAGER_H
