#ifndef GROUPCREATOR_H
#define GROUPCREATOR_H

#include <QWidget>
#include "classes/database.h"
#include <QStandardItemModel>
#include <QKeyEvent>

namespace Ui {
class GroupCreator;
}

class GroupCreator : public QWidget
{
    Q_OBJECT

public:
    explicit GroupCreator(QWidget *parent = 0);
    ~GroupCreator();

private slots:
    void on_addMemberButton_clicked();
    void on_removeMemberButton_clicked();
    void on_groupSizeMin_valueChanged(int arg1);
    void on_groupSizeMax_valueChanged(int arg1);
    void on_mixGroups_clicked();
    void on_groupSizeOptions_currentIndexChanged(int index);
    void on_groupSizeOptions_activated(const QString &arg1);
    void on_addAllMemberButton_clicked();
    void on_removeAllMemberButton_clicked();
    void on_gotoCreateGroupsPage_clicked();
    void on_gotoSelectMembersPage_clicked();
    void on_adminPersonsButton_clicked();
    void on_copyToClipboard_clicked();
    void on_useTeamNameInList_clicked();
    void on_availableMembers_doubleClicked(const QModelIndex &index);
    void on_selectedMembers_doubleClicked(const QModelIndex &index);
    void on_filterClass_activated(const QString &arg1);
    void on_helpButton1_clicked();
    void on_filterGroupOptions_valueChanged(int arg1);

private:
    Ui::GroupCreator *ui;

    Database *database() const;
    void setDatabase(Database *database);
    Database *_database;

    QStandardItemModel *selectedMembers() const;
    void setSelectedMembers(QStandardItemModel *selectedMembers);
    QStandardItemModel *_selectedMembers;

    void copyToClipboard();

    //
    void createGroups();

    //
    void calulateGroupSizeOptions();

    //Medlemmer tabeller
    void updateAvailableMemebersTable();
    void addMember();
    void removeMember();

    //
    void filterGroupOptions(int groupSize);

protected:
    void keyPressEvent(QKeyEvent *event);


};

#endif // GROUPCREATOR_H
