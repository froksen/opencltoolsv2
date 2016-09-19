#ifndef THINGSELECTORADMIN_H
#define THINGSELECTORADMIN_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ThingSelectorAdmin;
}

class ThingSelectorAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ThingSelectorAdmin(QWidget *parent = 0);
    ~ThingSelectorAdmin();



private slots:
    void on_btnAdd_clicked();
    void on_cboExisting_editTextChanged(const QString &arg1);
    void on_btnDelete_clicked();
    void on_cboExisting_currentTextChanged(const QString &arg1);
    void on_btnSaveClose_clicked();
    void on_btnEdit_clicked();

private:
    Ui::ThingSelectorAdmin *ui;
    void setupDatabase();

    QSqlTableModel *model() const;
    void setModel(QSqlTableModel *model);
    QSqlTableModel *_model;

};

#endif // THINGSELECTORADMIN_H
