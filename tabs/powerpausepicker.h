#ifndef POWERPAUSEPICKER_H
#define POWERPAUSEPICKER_H

#include <QWidget>
#include "classes/randomnumber.h"
#include "classes/powerpausemanager.h"
#include <QSqlRecord>

namespace Ui {
class PowerPausePicker;
}

class PowerPausePicker : public QWidget
{
    Q_OBJECT

public:
    explicit PowerPausePicker(QWidget *parent = 0);
    ~PowerPausePicker();




private slots:
    void on_btnAdminPowerPause_clicked();


    void on_btnNewPowerPause_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::PowerPausePicker *ui;

    QSqlRecord currentRecord() const;
    void setCurrentRecord(const QSqlRecord &currentRecord);
    QSqlRecord _currentRecord;
    RandomNumber *randomNumber() const;

    PowerPauseManager *ppmgr() const;

    RandomNumber *_randomNumber;
    PowerPauseManager *_ppmgr;

protected:
        void resizeEvent(QResizeEvent*);

};

#endif // POWERPAUSEPICKER_H
