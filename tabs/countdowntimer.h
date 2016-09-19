#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QWidget>
#include <QTimer>
#include <QSound>
#include <QSoundEffect>

namespace Ui {
class CountDownTimer;
}

class CountDownTimer : public QWidget
{
    Q_OBJECT

public:
    explicit CountDownTimer(QWidget *parent = 0);
    ~CountDownTimer();


private slots:
    void timerTimeout();
    void tickTimerTimeout();
    void on_btnStartStop_clicked();
    void on_btnSetInterval_clicked();
    void on_btnReset_clicked();
        void toggleButtons();

        void on_view1000parts_clicked(bool checked);

        void on_cbJBEffekt_clicked();

private:
    Ui::CountDownTimer *ui;

    int getTimerInterval();
    int getTimerRemainingTime();
    bool setTimerInterval(int time);
    void resizeEvent(QResizeEvent*);


    QSoundEffect *getAudioPlayer() const;
    void setAudioPlayer(QSoundEffect *audioPlayer);


    bool runTimer();


    QTimer *timer;
    QTimer *tickTimer;
    int timerIntervalAtStart;

    QSoundEffect *_audioPlayer;


};

#endif // COUNTDOWNTIMER_H
