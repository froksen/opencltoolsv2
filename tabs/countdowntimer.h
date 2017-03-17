#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QWidget>
#include <QTimer>
#include <QSound>
#include <QMediaPlayer>

namespace Ui {
class CountDownTimer;
}

class CountDownTimer : public QWidget
{
    Q_OBJECT

public:
    explicit CountDownTimer(QWidget *parent = 0);
    ~CountDownTimer();


    bool getAlarmMode() const;
    void setAlarmMode(bool value);

private slots:
    void timerTimeout();
    void tickTimerTimeout();
    void on_btnStartStop_clicked();
    void on_btnSetInterval_clicked();
    void on_btnReset_clicked();
        void toggleButtons();

        void on_view1000parts_clicked(bool checked);

        void on_cbJBEffekt_clicked();

        void on_btnSetalarm_clicked();

        void alarmSelectorAccepted();
        void alarmSelector_alarmChanged(QString);

private:
    Ui::CountDownTimer *ui;

    int getTimerInterval();
    int getTimerRemainingTime();
    bool setTimerInterval(int time);
    void resizeEvent(QResizeEvent*);


    QMediaPlayer *getAudioPlayer() const;
    void setAudioPlayer(QMediaPlayer *audioPlayer);
    bool runTimer();

    bool alarmMode;

    QTimer *timer;
    QTimer *tickTimer;
    int timerIntervalAtStart;

    QMediaPlayer *_audioPlayer;


};

#endif // COUNTDOWNTIMER_H
