#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "classes/databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager *databaseManager() const;
    void setDatabaseManager(DatabaseManager *databaseManager);

private slots:
    void on_actionAfslut_triggered();
    void on_actionOm_triggered();
    void on_actionH_r_sangen_triggered();
    void on_actionFuldsk_rm_Vindue_triggered();

private:
    Ui::MainWindow *ui;

    DatabaseManager *_databaseManager;
};

#endif // MAINWINDOW_H
