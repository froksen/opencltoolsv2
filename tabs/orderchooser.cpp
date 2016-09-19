#include "orderchooser.h"
#include "ui_orderchooser.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QMessageBox>
#include "dialogs/peopleformadmin.h"

OrderChooser::OrderChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderChooser)
{
    ui->setupUi(this);

    //Indlæser DB
    setupDatabase();

    //Indlæser QSqlTableModel
    model = new QSqlTableModel(this);
    model->setTable("tblPersoner");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("navn"));
    model->setHeaderData(2, Qt::Horizontal, tr("Gruppe"));

    //Laver model til de valgte personer
    selectedPeopleModel = new QStandardItemModel(this);
    selectedPeopleModel->setHorizontalHeaderItem(0, new QStandardItem("id"));
    selectedPeopleModel->setHorizontalHeaderItem(1, new QStandardItem("navn"));
    //selectedPeopleModel->setHorizontalHeaderItem(2, new QStandardItem("Gruppe"));

    //Sikre at der kun kan vælges hele rækker.
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableSelectedPeople->setSelectionBehavior(QAbstractItemView::SelectRows);

    //Sætter modellen til tableView
    ui->tableView->setModel(model);
    ui->tableSelectedPeople->setModel(selectedPeopleModel);

    //Skjuler ID-kolonne
    ui->tableView->hideColumn(0);
    ui->tableSelectedPeople->hideColumn(0);

    //Tilpasser kolonnerne
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableSelectedPeople->horizontalHeader()->setStretchLastSection(true);

    //Skjuler tabBaren
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);

    //Sikre, at brugeren ikke kan gå videre uden, at have valgt nogle personer
    ui->btnPageSelectionForward->setEnabled(false);
}

OrderChooser::~OrderChooser()
{
    delete ui;
}

void OrderChooser::on_tableView_activated(const QModelIndex &index)
{
    qDebug() << index;
}

void OrderChooser::on_tableView_pressed(const QModelIndex &index)
{
    qDebug() << index.row();
}

void OrderChooser::on_btnCreateOrder_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    foreach(QModelIndex index,indexes){
        qDebug() << index;
    }

}

void OrderChooser::on_btnAddPerson_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();

    foreach(QModelIndex index,indexes){
        //Finder index´et af id og navn
        QModelIndex idIndex = ui->tableView->model()->index(index.row(), 0, QModelIndex());
        QModelIndex nameIndex = ui->tableView->model()->index(index.row(), 1, QModelIndex());

        //Finder indholdet af id´et
        QString id = ui->tableView->model()->data(idIndex).toString();
        QString name = ui->tableView->model()->data(nameIndex).toString();

        //Tilføjer til modellen over valgte personer.
        appendItemToSelectedPeopleModel(id,name);

        //Fjerner/skjuler fra modellen over mulige
        ui->tableView->hideRow(index.row());
    }

    checkInputs();
}

void OrderChooser::on_btnRemovePerson_clicked()
{
    QModelIndexList indexes = ui->tableSelectedPeople->selectionModel()->selectedRows();

    if(indexes.count()<1){
        return;
    }

    foreach(QModelIndex index,indexes){
        //Finder ID´et i tabellen over valgte personer
        QString idToRemove = index.data().toString();

        //Viser det igen i tabellen over mulige personer
        QModelIndexList indexes2 = ui->tableView->selectionModel()->selectedRows();
        foreach(QModelIndex index2,indexes2){
            QString idToShow = index2.data().toString();

            if(idToRemove==idToShow){
                ui->tableView->showRow(index2.row());
            }
        }

        //Fjerner fra valgte liste
        getSelectedPeopleModel()->removeRow(index.row());
    }

    checkInputs();
}

void OrderChooser::on_sbPeoplePerGroup_editingFinished()
{


}

void OrderChooser::on_sbPeoplePerGroup_valueChanged(int arg1)
{
    createGroups();
}

void OrderChooser::createGroups()
{
    //Hvor mange der er valgt
    double peopleSelected = getSelectedPeopleModel()->rowCount();
    if(peopleSelected<1){
        return;
    }

    //Nulstiller tabellen
    ui->tableWidgetGroups->clear();

    //Sikre, at der ikke kan laves flere grupper end personer
    ui->sbPeoplePerGroup->setMaximum(peopleSelected);

    //Hvor mange personer der ønskes pr. gruppe
    double peoplePerGroup = ui->sbPeoplePerGroup->value();

    //Hvor mange grupper der er nødvendige
    double groupsNeeded = ceil(peopleSelected/peoplePerGroup);

    qDebug() << "People selected:" << peopleSelected;
    qDebug() << "People per group:" << peoplePerGroup;
    qDebug() << "Groups needed:" << groupsNeeded;

    //Hvor mange kolonner der skal være
    ui->tableWidgetGroups->setColumnCount(groupsNeeded);
    ui->tableWidgetGroups->setRowCount(peoplePerGroup);

    //Sætter ediketten til grupperne
    for(int i=0;i<=groupsNeeded;i++){
        ui->tableWidgetGroups->setHorizontalHeaderItem(i,new QTableWidgetItem(QString("Gruppe %1").arg(i+1)));
    }

    QStringList selectedPersons;
    for(int i=0;i<getSelectedPeopleModel()->rowCount();i++){
        QString person = getSelectedPeopleModel()->item(i,1)->text();

        selectedPersons.append(person);
    }


    int groupColNum = 0;
    int curPeoplePerGroup = 0;
    while(selectedPersons.count()>0){
        //Vælger personen;
        int personIndexNum = getRandomNumberBetween(0,selectedPersons.count()-1);
        QString personName = selectedPersons.at(personIndexNum);

        //Hvis gruppen er fyldt op
        if(curPeoplePerGroup>=peoplePerGroup){
            curPeoplePerGroup = 0;
            groupColNum++;
        }

        //Tilføjer til UI
        QTableWidgetItem *newItem = new QTableWidgetItem(personName);
        ui->tableWidgetGroups->setItem(curPeoplePerGroup,groupColNum,newItem);

        //Sletter personen fra listen
        selectedPersons.removeAt(personIndexNum);

        //++
        curPeoplePerGroup++;
    }

    return;
}

void OrderChooser::checkInputs()
{
    int peopleSelected = getSelectedPeopleModel()->rowCount();

    ui->btnPageSelectionForward->setEnabled(false);

    if(peopleSelected > 0){
        ui->btnPageSelectionForward->setEnabled(true);
    }
}

QSqlDatabase OrderChooser::setupDatabase()
{
    //Database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //QSqlDatabase db = QSqlDatabase::database("QSQLITE");
    db.setDatabaseName("db.sqlite");

    //Åbner DB
    if(!db.open()){
        qDebug() << "DB Open: Failed";
        qDebug() << db.lastError().text();
    }
    else{
        qDebug() << "DB Open: Success";
    }

    //Lukker databasen igen
    db.close();
    QSqlDatabase::removeDatabase("db.sqlite");

    return db;
}

int OrderChooser::getRandomNumberBetween(int low, int high)
{
    int randomNumber = qrand() % ((high + 1) - low) + low;
    return randomNumber;
}

void OrderChooser::on_btnCreateGroups_clicked()
{
    createGroups();
}

void OrderChooser::on_btnPageSelectionForward_clicked()
{
    createGroups();
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
}

void OrderChooser::on_btnPageGroupsBack_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
}


QStandardItemModel *OrderChooser::getSelectedPeopleModel() const
{
    return selectedPeopleModel;
}

void OrderChooser::appendItemToSelectedPeopleModel(QString id, QString name)
{
    int nextRow = selectedPeopleModel->rowCount();
    qDebug() << "Adding item (id name)" << id << name << "to row" << nextRow;

    selectedPeopleModel->setItem(nextRow,0,new QStandardItem(id));
    selectedPeopleModel->setItem(nextRow,1,new QStandardItem(name));
}


void OrderChooser::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_btnAddPerson_clicked();;
}

void OrderChooser::on_tableSelectedPeople_doubleClicked(const QModelIndex &index)
{
    on_btnRemovePerson_clicked();
}

void OrderChooser::on_btnPersonNew_clicked()
{
    peopleFormAdmin *m = new peopleFormAdmin(this);

    m->exec();

    m = NULL;
    delete m;
    updateDBModel();
}

void OrderChooser::updateDBModel()
{
    qDebug() << "Updating DB model";
    setupDatabase();

    if(model){
        model = 0;
        delete model;
    }

    model = new QSqlTableModel(this);
    model->setTable("tblPersoner");
    model->select();

    ui->tableView->setModel(model);
}

void OrderChooser::on_btnPersonEdit_clicked()
{
    //Sikre, at der kun er valgt en bruger
    int selectedUsersCount = ui->tableView->selectionModel()->selectedRows().count();
    if(selectedUsersCount>1){
       QMessageBox::information(this,"Redigering af person","Du må kun markere en person af gangen.");
       return;
    }

    //Den vaglte brugers id;
    int id = ui->tableView->selectionModel()->selectedRows().at(0).data().toInt(); //ui->tableView->selectionModel()->select(ui->tableView->currentIndex(),QItemSelectionModel::Select);

    //Indlæser dialogen
    peopleFormAdmin *m = new peopleFormAdmin(this);
    m->loadRecord(id);
    m->exec();

    m = NULL;
    delete m;
    updateDBModel();
}

void OrderChooser::on_btnPersonDelete_clicked()
{
    //Sikre, at der kun er valgt en bruger
    int selectedUsersCount = ui->tableView->selectionModel()->selectedRows().count();
    if(selectedUsersCount>1){
       QMessageBox::information(this,"Sletning af person","Du må kun markere en person af gangen.");
       return;
    }

    //Spørger brugeren om der skal fortsættes.
    int answer = QMessageBox::question(this,"Sletning af person","Er du sikker på, at du vil slette personen? Handlingen kan ikke fortrydes!",QMessageBox::Yes,QMessageBox::No);
    if(answer != QMessageBox::Yes ){
        return;
    }

    //Den vaglte brugers id;
    int id = ui->tableView->selectionModel()->selectedRows().at(0).data().toInt();
    peopleFormAdmin *m = new peopleFormAdmin(this);
    if(m->deleteRecord(id)){
        QMessageBox::information(this,"Sletning af person","Sletningen af personen lykkes!");
    }
    else {
        QMessageBox::critical(this,"Sletning af person","Sletningen af personen mislykkes!");
    }

    //Sletter Pointer
    m = NULL;
    delete m;

    //Opdaterer modellen.
    updateDBModel();
}
