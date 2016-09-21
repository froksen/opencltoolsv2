#ifndef POWERPAUSEADMIN_H
#define POWERPAUSEADMIN_H

#include <QDialog>
#include "QSqlTableModel"
#include "classes/powerpausemanager.h"

namespace Ui {
class PowerPauseAdmin;
}

class PowerPauseAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit PowerPauseAdmin(QWidget *parent = 0);
    ~PowerPauseAdmin();

private slots:
    void on_pushButton_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_btnNew_clicked();
    void on_tableView_entered(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::PowerPauseAdmin *ui;
    PowerPauseManager *ppMgr() const;

    //Voids
    void loadExistingPowerPauses();

    PowerPauseManager *_ppMgr;



};

#endif // POWERPAUSEADMIN_H
