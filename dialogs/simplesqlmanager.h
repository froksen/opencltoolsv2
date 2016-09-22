#ifndef SIMPLESQLMANAGER_H
#define SIMPLESQLMANAGER_H

#include <QDialog>
#include <QSqlTableModel>
#include "classes/databasemanager.h"

namespace Ui {
class SimpleSqlManager;
}

class SimpleSqlManager : public QDialog
{
    Q_OBJECT

public:
    explicit SimpleSqlManager(QWidget *parent = 0);
    ~SimpleSqlManager();

    void loadTable(QString tableName);
    void setDataType(QString text);

    int visibleColumn() const;
    void setVisibleColumn(int visibleColumn);



private slots:
    void on_btnAdd_clicked();
    void on_cboExisting_editTextChanged(const QString &arg1);
    void on_btnDelete_clicked();
    void on_cboExisting_currentTextChanged(const QString &arg1);
    void on_btnSaveClose_clicked();
    void on_btnEdit_clicked();

private:
    Ui::SimpleSqlManager *ui;
    void setupDatabase();

    QSqlTableModel *model() const;
    void setModel(QSqlTableModel *model);
    QSqlTableModel *_model;

    void reloadTable();

    DatabaseManager *databaseManager() const;
    void setDatabaseManager(DatabaseManager *databaseManager);
    DatabaseManager *_databaseManager;

    QString tableName() const;
    void setTableName(const QString &tableName);
    QString _tableName;

    int _visibleColumn = 0;

};

#endif // SIMPLESQLMANAGER_H
