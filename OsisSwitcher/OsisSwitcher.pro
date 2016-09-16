#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T13:03:27
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OsisSwitcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../OsisProxy/isucalclink.cpp \
    ../OsisProxy/dataqueue.cpp \
    osis/dataparser.cpp \
    osis/competitiondata.cpp \
    osis/element/action.cpp \
    osis/element/athlete.cpp \
    osis/element/category.cpp \
    osis/element/criteria.cpp \
    osis/element/deduction.cpp \
    osis/element/element.cpp \
    osis/element/elementlist.cpp \
    osis/element/event.cpp \
    osis/element/isuosis.cpp \
    osis/element/majoritydeduction.cpp \
    osis/element/official.cpp \
    osis/element/participant.cpp \
    osis/element/performance.cpp \
    osis/element/prfdetails.cpp \
    osis/element/prfranking.cpp \
    osis/element/segment.cpp \
    osis/element/segmentrunning.cpp \
    osis/element/segmentstart.cpp \
    osis/element/warmupgroup.cpp \
    osis/osisdata.cpp \
    obs/actions.cpp \
    obs/obsaction.cpp \
    obs/sceneinfo.cpp \
    obs/sceneswitcher.cpp \
    obs/scenetableui.cpp \
    actiontoscene.cpp

HEADERS  += mainwindow.h \
    ../OsisProxy/isucalclink.h \
    ../OsisProxy/dataqueue.h \
    osis/dataparser.h \
    osis/competitiondata.h \
    osis/element/action.h \
    osis/element/athlete.h \
    osis/element/category.h \
    osis/element/criteria.h \
    osis/element/deduction.h \
    osis/element/element.h \
    osis/element/elementlist.h \
    osis/element/event.h \
    osis/element/isuosis.h \
    osis/element/majoritydeduction.h \
    osis/element/official.h \
    osis/element/participant.h \
    osis/element/performance.h \
    osis/element/prfdetails.h \
    osis/element/prfranking.h \
    osis/element/segment.h \
    osis/element/segmentrunning.h \
    osis/element/segmentstart.h \
    osis/element/warmupgroup.h \
    osis/osisdata.h \
    obs/actions.h \
    obs/obsaction.h \
    obs/sceneinfo.h \
    obs/sceneswitcher.h \
    obs/scenetableui.h \
    obsosisif.h \
    actiontoscene.h \
    trace.h

FORMS    += mainwindow.ui

INCLUDEPATH += \
    $$PWD/../OsisProxy \
    $$PWD/osis

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags)
GIT_VERSION ~= s/v/""

DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

VERSION = $$GIT_VERSION
VERSION ~= s/\.\d+\.[a-f0-9]{6,}//
