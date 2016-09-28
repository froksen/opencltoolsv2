#-------------------------------------------------
#
# Project created by QtCreator 2016-07-17T13:13:56
#
#-------------------------------------------------

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCLTools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabs/countdowntimer.cpp \
    dialogs/timeselector.cpp \
    tabs/selectorfinger.cpp \
    tabs/orderchooser.cpp \
    dialogs/peopleformadmin.cpp \
    classes/personinformation.cpp \
    classes/randomnumber.cpp \
    tabs/selectorrandomvalue.cpp \
    tabs/selectorthing.cpp \
    classes/animationshade.cpp \
    tabs/spinboard.cpp \
    classes/database.cpp \
    tabs/powerpausepicker.cpp \
    classes/powerpause.cpp \
    dialogs/powerpauseadmin.cpp \
    classes/powerpausemanager.cpp \
    dialogs/powerpauseform.cpp \
    dialogs/powerpauseviewer.cpp \
    tabs/CooperativeLearning/teamplate.cpp \
    tabs/groupcreator.cpp \
    dialogs/simplesqlmanager.cpp \
    classes/databasemanager.cpp \
    dialogs/sqlmanager.cpp \
    tabs/clock.cpp

HEADERS  += mainwindow.h \
    tabs/countdowntimer.h \
    dialogs/timeselector.h \
    tabs/selectorfinger.h \
    tabs/orderchooser.h \
    dialogs/peopleformadmin.h \
    classes/personinformation.h \
    classes/randomnumber.h \
    tabs/selectorrandomvalue.h \
    tabs/selectorthing.h \
    classes/animationshade.h \
    tabs/spinboard.h \
    classes/database.h \
    tabs/powerpausepicker.h \
    classes/powerpause.h \
    dialogs/powerpauseadmin.h \
    classes/powerpausemanager.h \
    dialogs/powerpauseform.h \
    dialogs/powerpauseviewer.h \
    tabs/CooperativeLearning/teamplate.h \
    tabs/groupcreator.h \
    dialogs/simplesqlmanager.h \
    classes/databasemanager.h \
    dialogs/sqlmanager.h \
    tabs/clock.h


FORMS    += mainwindow.ui \
    tabs/countdowntimer.ui \
    dialogs/timeselector.ui \
    tabs/selectorfinger.ui \
    tabs/orderchooser.ui \
    dialogs/peopleformadmin.ui \
    tabs/selectorrandomvalue.ui \
    tabs/selectorthing.ui \
    classes/animationshade.ui \
    dialogs/thingselectoradmin.ui \
    tabs/spinboard.ui \
    tabs/powerpausepicker.ui \
    dialogs/powerpauseadmin.ui \
    dialogs/powerpauseform.ui \
    dialogs/powerpauseviewer.ui \
    tabs/CooperativeLearning/teamplate.ui \
    tabs/groupcreator.ui \
    dialogs/simplesqlmanager.ui \
    dialogs/sqlmanager.ui \
    tabs/clock.ui

RESOURCES += \
    resource.qrc

DISTFILES +=

