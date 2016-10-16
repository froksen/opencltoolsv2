#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>

namespace Ui {
class StopWatch;
}

class StopWatch : public QWidget
{
    Q_OBJECT

public:
    explicit StopWatch(QWidget *parent = 0);
    ~StopWatch();

private:
    Ui::StopWatch *ui;
};

#endif // STOPWATCH_H
