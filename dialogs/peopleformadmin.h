#ifndef PEOPLEFORMADMIN_H
#define PEOPLEFORMADMIN_H

#include <QDialog>
#include <QSqlDatabase>
#include "classes/personinformation.h"
#include <QSqlTableModel>

namespace Ui {
class peopleFormAdmin;
}

class peopleFormAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit peopleFormAdmin(QWidget *parent = 0);
    ~peopleFormAdmin();

    int getPersonId() const;
    void setPersonId(int value);

    QString getPersonName() const;
    void setPersonName(const QString &value);
    void loadRecord(int id);
    bool deleteRecord(int id);

private slots:
    void on_lineEditName_editingFinished();

    void on_buttonBox_accepted();

private:
    Ui::peopleFormAdmin *ui;


    bool newRecord();
    bool updateRecord(int id);
    void setLoadedPersonInformation();
    PersonInformation *getLoadedPersonInformation() const;

    PersonInformation *loadedPersonInformation;

    PersonInformation *getInformation(int id);

    QSqlDatabase db;

    int personId;
    QString personName;

    QSqlTableModel *infoModel;
};

#endif // PEOPLEFORMADMIN_H
