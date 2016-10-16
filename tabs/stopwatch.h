#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class StopWatch;
}

class StopWatch : public QWidget
{
    Q_OBJECT

public:
    explicit StopWatch(QWidget *parent = 0);
    ~StopWatch();

    QString timeFormat() const;
    void setTimeFormat(const QString &timeFormat);

private slots:
    void updateTimer();
    void on_StartStopButton_clicked();
    void on_ResetButton_clicked();
    void on_showHours_clicked();
    void on_showMinuts_clicked();

private:
    Ui::StopWatch *ui;

    QTimer *tickTimer() const;
    void setTickTimer(QTimer *tickTimer);

    quint64 time() const;
    void setTime(const quint64 &time);

    void updateFormat();

    QString _timeFormat;
    QTimer *_tickTimer;
    quint64 _time;
};

#endif // STOPWATCH_H
