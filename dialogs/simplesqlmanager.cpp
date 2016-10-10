#include "simplesqlmanager.h"
#include "ui_simplesqlmanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QInputDialog>
#include "classes/database.h"


SimpleSqlManager::SimpleSqlManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimpleSqlManager)
{
    ui->setupUi(this);
}

SimpleSqlManager::~SimpleSqlManager()
{
    delete ui;
}


void SimpleSqlManager::reloadTable()
{

    //Forbindelse til DB
    QSqlDatabase db = QSqlDatabase::database("default_connection",true);
    if(!db.isOpen()){
        qDebug() << "Læsning af databasen mislykkedes.";
        qDebug() << db.lastError().text();
    }

    //QScopedPointer<QSqlTableModel> model(new QSqlTableModel(this,db));
    QSqlTableModel *model = new QSqlTableModel(this,db); //Brugt "rigtig" pointer, da jeg ikke kan få ScopedPointer til at virke.
    model->setTable(tableName());
    if(!model->select()){
        qDebug() << "Læsning af tabel" << "startbythings" << "mislykkedes!";
        qDebug() << model->lastError().text();
    }

    ui->cboExisting->setModel(model);
    ui->cboExisting->setModelColumn(visibleColumn());
    ui->cboExisting->setFocus();

    //Delete pointer
    model = NULL;
    delete model;
}

DatabaseManager *SimpleSqlManager::databaseManager() const
{
    return _databaseManager;
}

void SimpleSqlManager::setDatabaseManager(DatabaseManager *databaseManager)
{
    _databaseManager = databaseManager;
}

QString SimpleSqlManager::tableName() const
{
    return _tableName;
}

void SimpleSqlManager::setTableName(const QString &tableName)
{
    _tableName = tableName;
}

int SimpleSqlManager::visibleColumn() const
{
    return _visibleColumn;
}

void SimpleSqlManager::setVisibleColumn(int visibleColumn)
{
    _visibleColumn = visibleColumn;
}

void SimpleSqlManager::loadTable(QString tableName)
{
    setTableName(tableName);
    reloadTable();
}

void SimpleSqlManager::setDataType(QString text)
{
    ui->dataTypeLabel->setText(text + " *");
}

void SimpleSqlManager::on_btnAdd_clicked()
{
    bool ok;
    QString newText = QInputDialog::getText(this, tr("Indtast ny"),
                                            tr("Ny:"), QLineEdit::Normal,
                                            "<Skriv her>", &ok);

    if(!ok && newText.isEmpty()){
        return;
    }

    ui->cboExisting->addItem(newText);
    ui->cboExisting->model()->submit();

//    QSqlRecord record =ui->cboExisting;// = new QSqlRecord(); = //ui->cboExisting->model()model()->record();
//    //record.setValue();
//    record.setValue(visibleColumn(),newText);
//    ui->cboExisting->model()->insert
//    model()->insertRecord(-1,record);
//    model()->submitAll();
//    reloadTable();
//    ui->cboExisting->setCurrentIndex(model()->rowCount()-1);
}


void SimpleSqlManager::on_cboExisting_editTextChanged(const QString &arg1)
{
    ui->cboExisting->setItemText(ui->cboExisting->currentIndex(),arg1);
    ui->cboExisting->model()->submit();

}

void SimpleSqlManager::on_btnDelete_clicked()
{
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::Question);
    msgbox.setText("Er du sikker på, at du vil slette det valgte? Handlingen kan ikke fortrydes.");
    msgbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);

    if(msgbox.exec() != QMessageBox::Yes){
        return;
    }

    ui->cboExisting->removeItem(ui->cboExisting->currentIndex());
    ui->cboExisting->model()->submit();

    msgbox.setIcon(QMessageBox::Information);
    msgbox.setText("Slettet!");
    msgbox.setStandardButtons(QMessageBox::Ok);
    msgbox.exec();

    reloadTable();
    ui->cboExisting->setCurrentIndex(0);

}

void SimpleSqlManager::on_cboExisting_currentTextChanged(const QString &arg1)
{
    on_cboExisting_editTextChanged(arg1);
}

void SimpleSqlManager::on_btnSaveClose_clicked()
{
        ui->cboExisting->model()->submit();
        this->close();
}

void SimpleSqlManager::on_btnEdit_clicked()
{
    bool ok;
    QString oldText = ui->cboExisting->currentText();
    QString text = QInputDialog::getText(this, tr("Ændringer"),
                                            tr("Rediger:"), QLineEdit::Normal,
                                            oldText, &ok);

    if(ok && !text.isEmpty()){
        ui->cboExisting->setItemText(ui->cboExisting->currentIndex(),text);
        ui->cboExisting->model()->submit();
    }

    reloadTable();
}
