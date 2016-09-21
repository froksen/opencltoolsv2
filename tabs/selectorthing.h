#ifndef SELECTORTHING_H
#define SELECTORTHING_H

#include <QWidget>
#include "classes/randomnumber.h"
#include "classes/animationshade.h"
#include "classes/databasemanager.h"

namespace Ui {
class SelectorThing;
}

class SelectorThing : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorThing(QWidget *parent = 0);
    ~SelectorThing();

private slots:
    void on_btnNewOutcome_clicked();

    void on_btnManageOptions_clicked();

private:
    Ui::SelectorThing *ui;

    void loadOutcomes();

    QStringList getOutcomes() const;
    void appendOutcomes(const QString value);
    QString getNewOutcome();

    void fitTextToLabel();

    RandomNumber rndNum;
    QStringList outcomes;

    AnimationShade *animationShade;

    DatabaseManager *getDatabasemanager() const;
    void setDatabasemanager(DatabaseManager *databasemanager);
    DatabaseManager *_databasemanager;


protected:
    void resizeEvent(QResizeEvent*);
};

#endif // SELECTORTHING_H
