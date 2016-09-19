#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QAbstractItemModel>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    bool execQry(QString qry);
    QSqlTableModel *selectTable(QString tableName, QString createTableQry="");
    bool isOpen();
    QSqlTableModel *refreshTable();

    QString getTableName() const;
    void setTableName(const QString &tableName);
private:
    bool connect();
    QSqlDatabase getDb() const;
    void setDb(QSqlDatabase value);

    QSqlDatabase db;

    QString _tableName;

signals:

public slots:



};

#endif // DATABASE_H
