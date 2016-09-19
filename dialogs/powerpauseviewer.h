#ifndef POWERPAUSEVIEWER_H
#define POWERPAUSEVIEWER_H

#include <QDialog>

namespace Ui {
class PowerPauseViewer;
}

class PowerPauseViewer : public QDialog
{
    Q_OBJECT

public:
    explicit PowerPauseViewer(QWidget *parent = 0);
    ~PowerPauseViewer();

private:
    Ui::PowerPauseViewer *ui;
};

#endif // POWERPAUSEVIEWER_H
