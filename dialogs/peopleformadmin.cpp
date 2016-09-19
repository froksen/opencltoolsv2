#include "peopleformadmin.h"
#include "ui_peopleformadmin.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

peopleFormAdmin::peopleFormAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::peopleFormAdmin)
{
    ui->setupUi(this);

    //Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    //Åbner DB
    if(!db.open()){
        qDebug() << "DB NOT open";
        qDebug() << db.lastError().text();
    }

    if(!db.tables().contains(QLatin1String("tblPersoner"))){
        qDebug() << "Table" << "tblPersoner" << "does not exists";
        QSqlQuery query;
        query.exec("CREATE TABLE `tblPersoner` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`navn` TEXT)");
        qDebug() << "tblPersoner create" << query.lastError();
    }

    //Laver model
    infoModel = new QSqlTableModel(this);
    infoModel->setTable("tblPersoner");
}

peopleFormAdmin::~peopleFormAdmin()
{
    delete ui;
}

int peopleFormAdmin::getPersonId() const
{
    return personId;
}

void peopleFormAdmin::setPersonId(int value)
{
    personId = value;
}

QString peopleFormAdmin::getPersonName() const
{
    return personName;
}

void peopleFormAdmin::setPersonName(const QString &value)
{
    personName = value;
}

void peopleFormAdmin::loadRecord(int id)
{
    //PersonInfo
    loadedPersonInformation = getInformation(id);

    //GUI
    ui->lineEditId->setText(QString::number(loadedPersonInformation->getId()));
    ui->lineEditName->setText(loadedPersonInformation->getName());
}

bool peopleFormAdmin::deleteRecord(int id)
{

    infoModel->setFilter(QString("id=%1").arg(id));
    infoModel->select();

    bool rlt = infoModel->removeRow(0);

    qDebug() << "Removed id:"<< id << rlt;

    infoModel->submitAll();
    return rlt;
}

bool peopleFormAdmin::newRecord()
{
    QSqlRecord record = infoModel->record();

    //record.setGenerated("id",true);
    record.setValue("navn",getPersonName());

    bool rlt = infoModel->insertRecord(-1,record);
    qDebug() << "Added new Item:"<< rlt;

    infoModel->submitAll();
    return rlt;
}

bool peopleFormAdmin::updateRecord(int id)
{
    qDebug() << "Trying to update record id:" << id;

    infoModel->setFilter(QString("id=%1").arg(id));
    qDebug() << " - Found id: " << infoModel->select();

    QSqlRecord record = infoModel->record(0);
    record.setValue("navn",getPersonName());

    bool rlt = infoModel->setRecord(0,record);

    qDebug() << " - Updated record:" << rlt;
    qDebug() << " - Saved changes:" << infoModel->submitAll();
    return rlt;
}

void peopleFormAdmin::setLoadedPersonInformation()
{
    if(!loadedPersonInformation){
        loadedPersonInformation = new PersonInformation(this);
    }

    loadedPersonInformation->setId(ui->lineEditId->text().toInt());
    loadedPersonInformation->setName(ui->lineEditName->text());
}

PersonInformation *peopleFormAdmin::getLoadedPersonInformation() const
{
    return loadedPersonInformation;
}

PersonInformation *peopleFormAdmin::getInformation(int id)
{
    infoModel->setFilter(QString("id=%1").arg(id));
    infoModel->select();

    int id1 = infoModel->record(0).value("id").toInt();
    QString name = infoModel->record(0).value("navn").toString();

    PersonInformation *pInfo = new PersonInformation(this);
    pInfo->setName(name);
    pInfo->setId(id1);


    return pInfo;
}


void peopleFormAdmin::on_lineEditName_editingFinished()
{
    setPersonName(ui->lineEditName->text());
}

void peopleFormAdmin::on_buttonBox_accepted()
{
    bool isNumber = false;

    int id = ui->lineEditId->text().toInt(&isNumber);

    //Hvis det er en eksisterende person
    if(isNumber){
        updateRecord(id);
    }
    else{
        newRecord();
    }

}
