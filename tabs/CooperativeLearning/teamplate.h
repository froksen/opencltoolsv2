#ifndef TEAMPLATE_H
#define TEAMPLATE_H

#include <QWidget>
#include <QImage>
#include <QPixmap>

namespace Ui {
class TeamPlate;
}

class TeamPlate : public QWidget
{
    Q_OBJECT

public:
    explicit TeamPlate(QWidget *parent = 0);
    ~TeamPlate();





private:
    Ui::TeamPlate *ui;

    QPixmap teamplatepixmap() const;
    void setTeamplatepixmap(const QPixmap &teamplatepixmap);
    void scaleTeamplateToLabel();
    QPixmap _teamplatepixmap;

protected:
    void resizeEvent(QResizeEvent*);
};

#endif // TEAMPLATE_H
