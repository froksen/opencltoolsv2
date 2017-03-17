#ifndef ALARMSELECTOR_H
#define ALARMSELECTOR_H

#include <QDialog>

namespace Ui {
class alarmselector;
}

class alarmselector : public QDialog
{
    Q_OBJECT

public:
    explicit alarmselector(QWidget *parent = 0);
    ~alarmselector();

private slots:
    void on_sbHours_valueChanged(int arg1);
    void on_sbMinuts_valueChanged(int arg1);
    void on_sbSecs_valueChanged(int arg1);
    void validateTime();

private:
    Ui::alarmselector *ui;
    bool beforeCurrentTime();
};

#endif // ALARMSELECTOR_H
