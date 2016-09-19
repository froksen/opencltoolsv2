#include "thingselectoradmin.h"
#include "ui_thingselectoradmin.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QInputDialog>
#include "classes/database.h"


ThingSelectorAdmin::ThingSelectorAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThingSelectorAdmin)
{
    ui->setupUi(this);

    //setupDatabase();

    Database *db = new Database(this);

    setModel(db->selectTable("startbythings"));
    model()->setTable("startbythings");
    model()->setEditStrategy(QSqlTableModel::OnRowChange);
    model()->select();

    ui->cboExisting->setModel(model());
    ui->cboExisting->setFocus();
}

ThingSelectorAdmin::~ThingSelectorAdmin()
{
    delete ui;
}

void ThingSelectorAdmin::setupDatabase()
{
    //Database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    //Åbner DB
    if(!db.open()){
        qDebug() << "DB Open: Failed";
        qDebug() << db.lastError().text();
    }

    //Lukker databasen igen
    db.close();
    QSqlDatabase::removeDatabase("db.sqlite");
}

QSqlTableModel *ThingSelectorAdmin::model() const
{
    return _model;
}

void ThingSelectorAdmin::setModel(QSqlTableModel *model)
{
    _model = model;
}

void ThingSelectorAdmin::on_btnAdd_clicked()
{
    bool ok;
    QString newText = QInputDialog::getText(this, tr("Skriv den nye sætning"),
                                            tr("Sætning:"), QLineEdit::Normal,
                                            "<Skriv din sætning her>", &ok);

    if(!ok && newText.isEmpty()){
        return;
    }

    QSqlRecord record = model()->record();
    record.setValue("text",newText);
    model()->insertRecord(-1,record);
    model()->submitAll();
}


void ThingSelectorAdmin::on_cboExisting_editTextChanged(const QString &arg1)
{
    ui->cboExisting->setItemText(ui->cboExisting->currentIndex(),arg1);
    ui->cboExisting->model()->submit();

}

void ThingSelectorAdmin::on_btnDelete_clicked()
{
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::Question);
    msgbox.setText("Er du sikker på, at du vil slette den valgte sætning? Handlingen kan ikke fortrydes.");
    msgbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);

    if(msgbox.exec() != QMessageBox::Yes){
        return;
    }

    ui->cboExisting->removeItem(ui->cboExisting->currentIndex());
    ui->cboExisting->model()->submit();

    msgbox.setIcon(QMessageBox::Information);
    msgbox.setText("Sætningen er blevet slettet!");
    msgbox.setStandardButtons(QMessageBox::Ok);
    msgbox.exec();

    ui->cboExisting->setCurrentIndex(0);
}

void ThingSelectorAdmin::on_cboExisting_currentTextChanged(const QString &arg1)
{
    on_cboExisting_editTextChanged(arg1);
}

void ThingSelectorAdmin::on_btnSaveClose_clicked()
{
        ui->cboExisting->model()->submit();
        this->close();
}

void ThingSelectorAdmin::on_btnEdit_clicked()
{
    bool ok;
    QString oldText = ui->cboExisting->currentText();
    QString text = QInputDialog::getText(this, tr("Lav dine ændringer"),
                                            tr("Sætning:"), QLineEdit::Normal,
                                            oldText, &ok);

    if(ok && !text.isEmpty()){
        ui->cboExisting->setItemText(ui->cboExisting->currentIndex(),text);
        ui->cboExisting->model()->submit();
    }
}
