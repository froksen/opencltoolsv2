#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();

private slots:
    void showTime();

private:
    Ui::Clock *ui;

protected:
    void resizeEvent(QResizeEvent*);
};

#endif // CLOCK_H
