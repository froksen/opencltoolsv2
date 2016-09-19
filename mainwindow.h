#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAfslut_triggered();

    void on_actionOm_triggered();

    void on_actionH_r_sangen_triggered();

    void on_actionFuldsk_rm_Vindue_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
