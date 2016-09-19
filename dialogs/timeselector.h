#ifndef TIMESELECTOR_H
#define TIMESELECTOR_H

#include <QDialog>
#include <QTime>
#include <QAbstractButton>

namespace Ui {
class TimeSelector;
}

class TimeSelector : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSelector(QWidget *parent = 0);
    ~TimeSelector();

    QTime getTime();
    void setTime(QTime time);
    void setTime(int time_ms);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::TimeSelector *ui;

    //void setUITime(time_ms);
};

#endif // TIMESELECTOR_H
