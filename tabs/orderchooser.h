#ifndef ORDERCHOOSER_H
#define ORDERCHOOSER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStringListModel>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QStandardItemModel>

namespace Ui {
class OrderChooser;
}

class OrderChooser : public QWidget
{
    Q_OBJECT

public:
    explicit OrderChooser(QWidget *parent = 0);
    ~OrderChooser();

    QStandardItemModel *getSelectedPeopleModel() const;
    void appendItemToSelectedPeopleModel(QString id, QString name);

private slots:
    void on_tableView_activated(const QModelIndex &index);
    void on_tableView_pressed(const QModelIndex &index);
    void on_btnCreateOrder_clicked();
    void on_btnAddPerson_clicked();
    void on_btnRemovePerson_clicked();
    void on_sbPeoplePerGroup_editingFinished();
    void on_sbPeoplePerGroup_valueChanged(int arg1);
    void on_btnCreateGroups_clicked();
    void on_btnPageSelectionForward_clicked();
    void on_btnPageGroupsBack_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableSelectedPeople_doubleClicked(const QModelIndex &index);

    void on_btnPersonNew_clicked();

    void updateDBModel();

    void on_btnPersonEdit_clicked();

    void on_btnPersonDelete_clicked();

private:
    Ui::OrderChooser *ui;

    QSqlTableModel *model;
    QStandardItemModel *selectedPeopleModel;
    QStandardItemModel *modelSelectedPersons;

    void createGroups();
    void checkInputs();
    QSqlDatabase setupDatabase();

    int getRandomNumberBetween(int low, int high);

};

#endif // ORDERCHOOSER_H
