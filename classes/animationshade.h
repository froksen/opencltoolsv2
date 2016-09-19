#ifndef ANIMATIONSHADE_H
#define ANIMATIONSHADE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class AnimationShade;
}

class AnimationShade : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationShade(QWidget *parent = 0);
    ~AnimationShade();

public slots:
    void runAnimation();
    void showShade(bool state=true);

private slots:
    void timerTimeout();


private:
    Ui::AnimationShade *ui;

    void switchColor();
    bool bgWhite = true;
    int blinkCount = 0;
    bool showshade = true;

    QTimer *timer;
};

#endif // ANIMATIONSHADE_H
