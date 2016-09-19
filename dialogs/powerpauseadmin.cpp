#include "powerpauseadmin.h"
#include "ui_powerpauseadmin.h"
#include <QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include "dialogs/powerpauseform.h"
#include <QMessageBox>
#include <QBuffer>
#include <QDropEvent>
#include <QByteArray>
#include <QMimeData>

PowerPauseAdmin::PowerPauseAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerPauseAdmin)
{
    ui->setupUi(this);

    _ppMgr = new PowerPauseManager(this);

    //Indlæser powerpauser
    loadExistingPowerPauses();


}

PowerPauseAdmin::~PowerPauseAdmin()
{
    delete ui;
}

void PowerPauseAdmin::loadExistingPowerPauses()
{
   ppMgr()->loadAll();
   QSqlTableModel* tableModel = ppMgr()->getItemsModel();

   //Indstillinger for tableModel
   tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
   tableModel->setHeaderData(0, Qt::Horizontal, tr("id"));
   tableModel->setHeaderData(1, Qt::Horizontal, tr("Aktiv"));
   tableModel->setHeaderData(2, Qt::Horizontal, tr("Titel"));
   tableModel->setHeaderData(3, Qt::Horizontal, tr("Hjælpetekst"));
   tableModel->setHeaderData(4, Qt::Horizontal, tr("Billede"));

   //Indstillinger for UI
   ui->tableView->setModel(tableModel);
   ui->tableView->hideColumn(0);
   ui->tableView->hideColumn(3);
   ui->tableView->hideColumn(4);

   ui->tableView->horizontalHeader()->setStretchLastSection(true);
   ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

PowerPauseManager *PowerPauseAdmin::ppMgr() const
{
    return _ppMgr;
}

void PowerPauseAdmin::on_pushButton_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();

    //Ændre statuser for valgte powerpauser
    foreach(QModelIndex index,indexes){
        QModelIndex isActiveIndex = ui->tableView->model()->index(index.row(), 1, QModelIndex());

        if(ui->tableView->model()->data(isActiveIndex).toBool()){
            ui->tableView->model()->setData(isActiveIndex,false);
        }
        else{
            ui->tableView->model()->setData(isActiveIndex,true);
        }


    }
}

void PowerPauseAdmin::on_btnEdit_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows().count()<1){
        return;
    }

    if(ui->tableView->selectionModel()->selectedRows().count()>1){
        QMessageBox::information(this,"Redigering","Du må kun markere en PowerPause af gangen.");
        return;
    }

    //valgte række
    int selectedRow = ui->tableView->selectionModel()->selectedRows().first().row();

    //Index´et af de forskellige ting
    QModelIndex itemTitle = ui->tableView->model()->index(selectedRow, 2, QModelIndex());
    QModelIndex itemHelptext = ui->tableView->model()->index(selectedRow, 3, QModelIndex());
    QModelIndex itemImage = ui->tableView->model()->index(selectedRow, 4, QModelIndex());

    //Variabler
    QString title = ui->tableView->model()->data(itemTitle).toString();
    QString helptext = ui->tableView->model()->data(itemHelptext).toString();
    QByteArray pixmaparray = ui->tableView->model()->data(itemImage).toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(pixmaparray,"PNG");

    //Selve formularen
    PowerPauseForm *ppf = new PowerPauseForm(this);
    ppf->setTitle(title);
    ppf->setHelptext(helptext);
    ppf->setImage(pixmap);
    ppf->exec();

    //Opdater data i skema
    ui->tableView->model()->setData(itemTitle,ppf->title());
    ui->tableView->model()->setData(itemHelptext,ppf->helptext());

    //Laver billedet om til et ByteArray som kan gemmes i DB
    QPixmap newPicture = ppf->image();
                QByteArray bytes;
                QBuffer buffer(&bytes);
                buffer.open(QIODevice::WriteOnly);
                newPicture.save(&buffer, "PNG");

    ui->tableView->model()->setData(itemImage,bytes);
}

void PowerPauseAdmin::on_btnDelete_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows().count()<1){
        return;
    }

    if(ui->tableView->selectionModel()->selectedRows().count()>1){
        QMessageBox::information(this,"Sletning","Du må kun markere en PowerPause af gangen.");
        return;
    }

    int answer = QMessageBox::question(this,"Slet PowerPause","Er du sikker på, at du vil slette PowerPausen? Handlingen kan ikke fortrydes!",QMessageBox::Yes,QMessageBox::No);
    if(answer != QMessageBox::Yes ){
        return;
    }

    int recId = ui->tableView->selectionModel()->selectedRows().first().data().toInt();
    if(!ppMgr()->remove(recId)){
        QMessageBox::critical(this,"Slet PowerPause","Sletningen af PowerPausen mislykkes!");
        return;
    }

    //Genindlæser
    loadExistingPowerPauses();
}

void PowerPauseAdmin::on_btnNew_clicked()
{
    //Selve formularen
    PowerPauseForm *ppf = new PowerPauseForm(this);
    ppf->exec();

    if(ppf->title().isEmpty()){
        return;
    }

    QPixmap newPicture = ppf->image();
                QByteArray bytes;
                QBuffer buffer(&bytes);
                buffer.open(QIODevice::WriteOnly);
                newPicture.save(&buffer, "PNG");

    ppMgr()->append(ppf->title(),ppf->helptext(),bytes);

    //Genindlæser
    loadExistingPowerPauses();
}

void PowerPauseAdmin::on_tableView_entered(const QModelIndex &index)
{

}

void PowerPauseAdmin::on_tableView_doubleClicked(const QModelIndex &index)
{
   on_btnEdit_clicked();
}

