#include "sqlmanager.h"
#include "ui_sqlmanager.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlRecord>

SqlManager::SqlManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlManager)
{
    setDatabaseManager(new DatabaseManager);
    databaseManager()->open();

    ui->setupUi(this);
}

SqlManager::~SqlManager()
{
    delete ui;
}

DatabaseManager *SqlManager::databaseManager() const
{
    return _databaseManager;
}

void SqlManager::setDatabaseManager(DatabaseManager *databaseManager)
{
    _databaseManager = databaseManager;
}

QSqlTableModel *SqlManager::model() const
{
    return _model;
}

void SqlManager::setModel(QSqlTableModel *model)
{
    _model = model;
}


QStringList SqlManager::hiddenColumnNames() const
{
    return _hiddenColumnNames;
}

void SqlManager::setHiddenColumnNames(const QStringList &names)
{
    _hiddenColumnNames = names;
}

void SqlManager::loadData(QString tableName)
{
    QSqlTableModel *model = databaseManager()->selectTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    setModel(model);

    ui->tableView->setModel(model);

    //Sikre, at de kolonner der skal være skjulte er det.
    for(int i=0;i<model->columnCount();i++){
        QString modelColName = model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();

        if(hiddenColumnNames().contains(modelColName)){
            ui->tableView->hideColumn(i);
        }
    }
}

void SqlManager::on_addButton_clicked()
{
    QSqlRecord record = model()->record();
    model()->insertRecord(-1,record);
    model()->submitAll();

    model()->select();
}

void SqlManager::on_removeButton_clicked()
{
    foreach(QModelIndex index, ui->tableView->selectionModel()->selectedRows(0)){
        qDebug() << index.row();
        ui->tableView->model()->removeRow(index.row());
    }

    model()->submitAll();
    model()->select();

}

void SqlManager::on_buttonBox_accepted()
{
    model()->submitAll();
}
