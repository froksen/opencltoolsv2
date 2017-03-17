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

private:
    Ui::alarmselector *ui;
};

#endif // ALARMSELECTOR_H
