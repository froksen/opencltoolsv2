#include "groupcreator.h"
#include "ui_groupcreator.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include "classes/randomnumber.h"
#include "dialogs/simplesqlmanager.h"
#include <QTableWidgetItem>
#include <QClipboard>
#include <QKeySequence>
#include <QMessageBox>


GroupCreator::GroupCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupCreator)
{
    ui->setupUi(this);

    //Laver databasen
    setDatabase(new Database());


    //Opdaterer tabellen
    updateAvailableMemebersTable();
    setSelectedMembers(new QStandardItemModel);

    //calulateGroupSizeOptions();


    //Skjuler tabs
    ui->tabWidget->tabBar()->setHidden(true);

    ui->gotoCreateGroupsPage->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);

    //Tilpasser kolonnerne
    ui->selectedMembers->horizontalHeader()->setStretchLastSection(true);
    ui->availableMembers->horizontalHeader()->setStretchLastSection(true);

}

GroupCreator::~GroupCreator()
{
    delete ui;
}

Database *GroupCreator::database() const
{
    return _database;
}

void GroupCreator::setDatabase(Database *database)
{
    _database = database;
}

QStandardItemModel *GroupCreator::selectedMembers() const
{
    return _selectedMembers;
}

void GroupCreator::setSelectedMembers(QStandardItemModel *selectedMembers)
{
    _selectedMembers = selectedMembers;
    ui->selectedMembers->setModel(selectedMembers);
    ui->selectedMembers->setSelectionBehavior(QAbstractItemView::SelectRows);

    selectedMembers->setHorizontalHeaderItem(0, new QStandardItem("Id"));
    selectedMembers->setHorizontalHeaderItem(1, new QStandardItem("Navn"));

    ui->selectedMembers->hideColumn(0);
}

void GroupCreator::copyToClipboard()
{
    //FRA: http://stackoverflow.com/questions/1230222/selected-rows-line-in-qtableview-copy-to-qclipboard
    QString clipboardString;
    QModelIndexList selectedIndexes = ui->groupsOverview->selectionModel()->selectedIndexes();

    for (int i = 0; i < selectedIndexes.count(); ++i)
    {
        QModelIndex current = selectedIndexes[i];
        QString displayText = current.data(Qt::DisplayRole).toString();

        // If there exists another column beyond this one.
        if (i + 1 < selectedIndexes.count())
        {
            QModelIndex next = selectedIndexes[i+1];

            // If the column is on different row, the clipboard should take note.
            if (next.row() != current.row())
            {
                displayText.append("\n");
            }
            else
            {
                // Otherwise append a column separator.
                displayText.append("\t");
            }
        }
        clipboardString.append(displayText);
    }

    QApplication::clipboard()->setText(clipboardString);
}

//void GroupCreator::copyToClipboard()
//{
//    //FRA: http://stackoverflow.com/questions/1230222/selected-rows-line-in-qtableview-copy-to-qclipboard
//    QString clipboardString;
//    QModelIndexList selectedIndexes = ui->groupsOverview->selectionModel()->selectedIndexes();

//    for (int i = 0; i < selectedIndexes.count(); ++i)
//    {
//        QModelIndex current = selectedIndexes[i];
//        QString displayText = current.data(Qt::DisplayRole).toString();

//        // If there exists another column beyond this one.
//        if (i + 1 < selectedIndexes.count())
//        {
//            QModelIndex next = selectedIndexes[i+1];

//            // If the column is on different row, the clipboard should take note.
//            if (next.row() != current.row())
//            {
//                displayText.append("\n");
//            }
//            else
//            {
//                // Otherwise append a column separator.
//                displayText.append(" | ");
//            }
//        }
//        clipboardString.append(displayText);
//    }

//    QApplication::clipboard()->setText(clipboardString);
//}

void GroupCreator::createGroups()
{
    if(selectedMembers()->rowCount()<=0){
        qDebug() << "createGroups:" << "Ingen medlemmer valgt!";
        return;
    }

    //Tilføjer de mulige navne, til en liste
    QStringList names;
    qDebug() << "selectedMembers()->rowCount()" << selectedMembers()->rowCount();
    for(int i=0;i<selectedMembers()->rowCount();i++){
        names.append(selectedMembers()->item(i,1)->text());
    }
    qDebug() << "names.count()" << names.count();

    //Oplysningerne
    QStringList selectedOption = ui->groupSizeOptions->currentData().toStringList();

    int groupsCount = QString(selectedOption.at(0)).toInt();
    int groupsCount1 = QString(selectedOption.at(1)).toInt();
    int groupsCount2 = QString(selectedOption.at(2)).toInt();
    int groupSize1 = QString(selectedOption.at(3)).toInt();
    int groupSize2 = QString(selectedOption.at(4)).toInt();

    qDebug() << "groupSize1" << groupSize1;


    int currentColumn = 0;
    int currentRow = 0;
    int currentGroupsize = 0;

    //Nulstiller
    ui->groupsOverview->clear();
    ui->groupsOverview->setRowCount(0);

    //Hvor mange kolonner;
    ui->groupsOverview->setColumnCount(groupsCount);
    //ui->groupsOverview->setRowCount(4);


    qDebug() << "groupSize1" << groupSize1;

    for(int i=0; i<groupsCount1;i++){

        if(ui->groupsOverview->rowCount()<groupSize1){
            ui->groupsOverview->setRowCount(groupSize1);
        }

        for(int j=0;j<groupSize1;j++){
            //Sætter intervallet

             //Får værdien
            int index = 0;
            if(names.count()>1){
                 index = qrand() % ((names.count()+1) - 1) + 1;
                 index = index-1;
            }

             //Teksten i tabellen
             ui->groupsOverview->setItem(currentRow,currentColumn,new QTableWidgetItem(names.at(index)));
             //næste række
             currentRow++;
             qDebug() << "groupCount" << i <<"names.count" << names.count() << "index" << index << names.at(index);

             //Sletter fra listen
             names.removeAt(index);
        }
        //Næste kolonne
        currentColumn = i+1;
        currentRow = 0;
    }

    qDebug() << "REST" << names;

    qDebug() << names.count()-1;

    currentRow = 0;
    for(int i=0; i<groupsCount2;i++){

        if(ui->groupsOverview->rowCount()<groupSize2){
            ui->groupsOverview->setRowCount(groupSize2);
        }

        for(int j=0;j<groupSize2;j++){
            //Sætter intervallet

             //Får værdien
            int index = 0;
            if(names.count()>1){
                 index = qrand() % ((names.count()+1) - 1) + 1;
                 index = index-1;
            }

             //Teksten i tabellen
             ui->groupsOverview->setItem(currentRow,currentColumn,new QTableWidgetItem(names.at(index)));
             //næste række
             currentRow++;
             qDebug() << "groupCount" << i <<"names.count" << names.count() << "index" << index << names.at(index);

             //Sletter fra listen
             names.removeAt(index);
        }
        //Næste kolonne
        currentColumn++;
        currentRow = 0;
    }
}

void GroupCreator::calulateGroupSizeOptions()
{
    //Variabler
    int membersCount = selectedMembers()->rowCount();
    int max = ui->groupSizeMax->value();
    int min = ui->groupSizeMin->value();
    float groupsByMax = 0.00;
    QList<QList<int>> validDivisors;

    //Fjerner tidligere muligheder
    ui->groupSizeOptions->clear();

    if(membersCount<max){
        ui->groupSizeOptions->addItem("Fejl: Maks>Antal valgte medlemmer!");
        return;
    }

    if(max<=min){
        ui->groupSizeOptions->addItem("Fejl: Maks=>min!");
        qDebug() << "Beregning af grupper: Maximum gruppestørrelse er større end minimum gruppestørrelse!";
        return;
    }

    double divisor;
    int divisorInteger;
    for(int maxSize=min;maxSize<=max;maxSize++){
        //Hvor mange gange kan det divideres
        divisor = membersCount/maxSize;

        //Hvor mange hele gange kan det divideres
        divisorInteger = floor(divisor);

        qDebug() << "(double)membersCount/(double)maxSize" << (double)membersCount/(double)maxSize;
        if(1>(double)membersCount/(double)maxSize){
            qDebug() << "--->Continue!";
            continue;
        }

//       qDebug() << "divisor" << divisor;
//       qDebug() <<  "divisorInteger" << divisorInteger;

        //Hvis der er en rest.
        if(membersCount % maxSize != 0){
            //Trækker en fra, da denne gruppe er et kommatal
            divisorInteger = divisorInteger -1;

            //Undersøger hvilke tal i intervallet der kan give hele divisorer.
            for(int num=min;num<=maxSize;num++){
                //Hvor mange medlemmer minus, hvor meget der kan laves med maxgruppe størrelse
                int leftOver = membersCount - divisorInteger*maxSize;

                //Hvis der ikke er nogen rest
                if(leftOver%num == 0){
                    QList<int> value;

                    if(divisorInteger>0){
                        //Størrelsen af max-size grupper
                        value.append(maxSize);
                        //Hvor mange max-size grupper
                        value.append(divisorInteger);

                        //Størrelsen af resterende grupper
                        value.append(num);
                        //Hvor mange gange det går op i leftOver
                        value.append(leftOver/num);
                        //Tilføjer til listen
                        validDivisors.append(value);
                    }

                }
            }
        }
        else{
            QList<int> value;

            //Størrelsen af hele grupper
            value.append(maxSize);
            //Hvor mange hele grupper
            value.append(divisorInteger);

            //Størrelsen af resterende grupper
            value.append(0);
            //Hvor mange gange det går op i leftOver
            value.append(0);

            //Tilføjer til listen
            validDivisors.append(value);
        }

    }

    //Tilføjer til Combobox
    foreach(QList<int> divisor, validDivisors){
        int groupCount = divisor.at(1) + divisor.at(3);
        int groupCount1 = divisor.at(1);
        int groupCount2 = divisor.at(3);
        int groupSize1 = divisor.at(0);
        int groupSize2 = divisor.at(2);

        QString text;

        class Pural
        {
           public:
            QString group(int size){
                if(size==1){
                    return QString::number(size)+" gruppe";
                }
                return QString::number(size)+" grupper";;
            }
            QString member(int size){
                if(size==1){
                    return QString::number(size)+" medlem";;
                }
                return QString::number(size)+" medlemmer";;
            }
        };

        Pural mPural;
        if(divisor.at(3)<=0){
           text = QString("(%0) %1 á %2").arg(mPural.group(divisor.at(1))).arg(mPural.group(groupCount)).arg(mPural.member(divisor.at(0)));
        }
        else if(divisor.at(1)<=0){
           text = QString("(%0) %1 á %2").arg(mPural.group(divisor.at(3))).arg(mPural.group(groupCount)).arg(mPural.member(divisor.at(0)));
        }
        else {
            text = QString("(%0) %1 á %2 og %3 á %4").arg(mPural.group(groupCount)).arg(mPural.group(divisor.at(1))).arg(mPural.member(divisor.at(0))).arg(mPural.group(divisor.at(3))).arg(mPural.member(divisor.at(2)));
        }

        QStringList itemData;
        itemData.append(QString::number(groupCount));
        itemData.append(QString::number(groupCount1));
        itemData.append(QString::number(groupCount2));
        itemData.append(QString::number(groupSize1));
        itemData.append(QString::number(groupSize2));

        qDebug () << divisor;
        ui->groupSizeOptions->setInsertPolicy(QComboBox::InsertAlphabetically);
        ui->groupSizeOptions->addItem(text,itemData);
    }

    //Opdaterer label
    ui->GroupSizeOptionsCount->setText("(" + QString::number(ui->groupSizeOptions->count()) + ")");

}


void GroupCreator::updateAvailableMemebersTable()
{
    QString createQry;

    createQry = "CREATE TABLE `tblPersoner` ("
                "`id`	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "`navn`	TEXT"
            ");";

    ui->availableMembers->setModel(database()->selectTable("tblPersoner",createQry));
    ui->availableMembers->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->availableMembers->hideColumn(0);

//    ui->availableMembers->model()->set->setHorizontalHeaderItem(0, new QStandardItem("Id"));
//    selectedMembers->setHorizontalHeaderItem(1, new QStandardItem("Navn"));

    ui->selectedMembers->hideColumn(0);
}

void GroupCreator::addMember()
{
    QModelIndexList indexes = ui->availableMembers->selectionModel()->selectedRows();

    foreach(QModelIndex index,indexes){
        //Finder index´et af id og navn
        QModelIndex idIndex = ui->availableMembers->model()->index(index.row(), 0, QModelIndex());
        QModelIndex nameIndex = ui->availableMembers->model()->index(index.row(), 1, QModelIndex());

        //Finder indholdet af id´et
        QString id = ui->availableMembers->model()->data(idIndex).toString();
        QString name = ui->availableMembers->model()->data(nameIndex).toString();

        //Tilføjer til modellen over valgte personer.
        int rowCount = selectedMembers()->rowCount();
        selectedMembers()->setItem(rowCount,0,new QStandardItem(id));
        selectedMembers()->setItem(rowCount,1,new QStandardItem(name));

        //Fjerner/skjuler fra modellen over mulige
        ui->availableMembers->hideRow(index.row());
    }

    ui->availableMembers->clearSelection();
}

void GroupCreator::removeMember()
{
    //ID´er der skal fjernes fra valgte liste
    QList<int> rowsToRemove;

    //Vender listen om, da det løser problemer længere nede.
    QModelIndexList indexes = ui->selectedMembers->selectionModel()->selectedRows();
    QModelIndexList rev_indexes;

    for(int i=indexes.count();i>0;i--){
        rev_indexes.append(indexes.at(i-1));
    }
    indexes = rev_indexes;

    //For hver af indexene
    foreach(QModelIndex index,indexes){
        //Finder index´et af id og navn
        QModelIndex idIndex = ui->selectedMembers->model()->index(index.row(), 0, QModelIndex());

        //Finder indholdet af id´et
        QString id = ui->selectedMembers->model()->data(idIndex).toString();

        //Viser det igen i tabellen over mulige personer
        ui->availableMembers->selectAll();
        QModelIndexList indexes2 = ui->availableMembers->selectionModel()->selectedRows();
        foreach(QModelIndex index2,indexes2){
            QString idToShow = index2.data().toString();

            if(id==idToShow){
                ui->availableMembers->showRow(index2.row());
                selectedMembers()->removeRow(index.row());
            }
        }
        //Fjerner/skjuler fra modellen over mulige
        rowsToRemove.append(index.row());
    }

    ui->availableMembers->clearSelection();
}

void GroupCreator::keyPressEvent(QKeyEvent *event)
{
    if(event->matches( QKeySequence::Copy )){
        copyToClipboard();
    }
}

void GroupCreator::on_addMemberButton_clicked()
{
    ui->gotoCreateGroupsPage->setEnabled(false);

    addMember();

    if(ui->selectedMembers->model()->rowCount()>1){
        ui->gotoCreateGroupsPage->setEnabled(true);
    }


}

void GroupCreator::on_removeMemberButton_clicked()
{
    ui->gotoCreateGroupsPage->setEnabled(false);

    removeMember();

    if(ui->selectedMembers->model()->rowCount()>1){
        ui->gotoCreateGroupsPage->setEnabled(true);
    }
}

void GroupCreator::on_groupSizeMin_valueChanged(int arg1)
{
    if(arg1>=ui->groupSizeMax->value()){
        ui->groupSizeMin->setValue(ui->groupSizeMax->value()-1);
        return;
    }

    calulateGroupSizeOptions();
}

void GroupCreator::on_groupSizeMax_valueChanged(int arg1)
{
    if(arg1<=ui->groupSizeMin->value()){
        ui->groupSizeMin->setValue(arg1-1);
        return;
    }

    if(selectedMembers()->rowCount()<arg1){
        ui->groupSizeMax->setValue(selectedMembers()->rowCount());
    }

    calulateGroupSizeOptions();
}

void GroupCreator::on_mixGroups_clicked()
{
    createGroups();
}

void GroupCreator::on_groupSizeOptions_currentIndexChanged(int index)
{
    //createGroups();
}

void GroupCreator::on_groupSizeOptions_activated(const QString &arg1)
{
    createGroups();
}

void GroupCreator::on_addAllMemberButton_clicked()
{
    //Fjerner dem fra listen først
    on_removeAllMemberButton_clicked();

    //Tilføjer dem alle igen. Sikre, at der ikke tilføjes flere gange.
    ui->availableMembers->selectAll();
    on_addMemberButton_clicked();
}

void GroupCreator::on_removeAllMemberButton_clicked()
{
    ui->selectedMembers->selectAll();
    on_removeMemberButton_clicked();
}

void GroupCreator::on_gotoCreateGroupsPage_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabCreateGroups);
    ui->groupSizeMax->setValue(selectedMembers()->rowCount());
    ui->groupSizeMin->setValue(1);
    calulateGroupSizeOptions();
}

void GroupCreator::on_gotoSelectMembersPage_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabSelectMembers);
}

void GroupCreator::on_adminPersonsButton_clicked()
{   
    SimpleSqlManager *dialog = new SimpleSqlManager(this);
    dialog->setVisibleColumn(1);
    dialog->loadTable("tblPersoner");
    dialog->loadTable("tblPersoner");
    dialog->setDataType("Personer");
    dialog->exec();


    ui->availableMembers->setModel(database()->refreshTable());
    ui->availableMembers->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->availableMembers->hideColumn(0);
}

void GroupCreator::on_copyToClipboard_clicked()
{
    ui->groupsOverview->selectAll();
    copyToClipboard();
    ui->groupsOverview->clearSelection();
    QMessageBox::information(this,"Kopiret","Tabellen er nu kopieret, indsæt nu teksten i Excel");
}
