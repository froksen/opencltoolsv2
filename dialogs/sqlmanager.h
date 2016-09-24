#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QDialog>
#include "classes/databasemanager.h"
#include <QSqlTableModel>

namespace Ui {
class SqlManager;
}

class SqlManager : public QDialog
{
    Q_OBJECT

public:
    explicit SqlManager(QWidget *parent = 0);
    ~SqlManager();
    void loadData(QString tableName);

    QStringList hiddenColumnNames() const;
    void setHiddenColumnNames(const QStringList &names);





private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::SqlManager *ui;

    DatabaseManager *databaseManager() const;
    void setDatabaseManager(DatabaseManager *databaseManager);
    DatabaseManager *_databaseManager;

    QStringList _hiddenColumnNames;

    QSqlTableModel *model() const;
    void setModel(QSqlTableModel *model);
    QSqlTableModel *_model;
};

#endif // SQLMANAGER_H
