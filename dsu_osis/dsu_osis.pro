#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T09:55:50
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dsu_osis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calcconnectionthread.cpp \
    osis/osisxml.cpp \
    osis/osisdata.cpp \
    isucompetition.cpp \
    osis/element/performance.cpp \
    osis/element/element.cpp \
    osis/element/warmupgroup.cpp \
    osis/element/prfranking.cpp \
    osis/element/segmentrunning.cpp \
    osis/element/action.cpp \
    osis/element/prfdetails.cpp \
    osis/element/event.cpp \
    osis/element/category.cpp \
    osis/element/criteria.cpp \
    osis/element/segmentstart.cpp \
    osis/element/athlete.cpp \
    osis/element/deduction.cpp \
    osis/element/majoritydeduction.cpp \
    osis/element/official.cpp \
    osis/element/participant.cpp \
    osis/element/segment.cpp \
    osis/element/isuosis.cpp \
    osis/element/elementlist.cpp \
    obs/actions.cpp \
    obs/sceneswitcher.cpp \
    obs/sceneinfo.cpp \
    obs/scenetableui.cpp \
    obs/obsaction.cpp

HEADERS  += mainwindow.h \
    calcconnectionthread.h \
    osis/osisxml.h \
    osis/osisdata.h \
    trace.h \
    isucompetition.h \
    osis/dataif.h \
    osis/competitionif.h \
    osis/element/performance.h \
    osis/element/element.h \
    osis/element/warmupgroup.h \
    osis/element/prfranking.h \
    osis/element/segmentrunning.h \
    osis/element/action.h \
    osis/element/prfdetails.h \
    osis/element/event.h \
    osis/element/category.h \
    osis/element/criteria.h \
    osis/element/segmentstart.h \
    osis/element/athlete.h \
    osis/element/deduction.h \
    osis/element/majoritydeduction.h \
    osis/element/official.h \
    osis/element/participant.h \
    osis/element/segment.h \
    osis/element/isuosis.h \
    osis/element/elementlist.h \
    obs/actions.h \
    obsosisif.h \
    obs/sceneswitcher.h \
    obs/sceneinfo.h \
    obs/scenetableui.h \
    obs/obsaction.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md \
    LICENSE.txt \
    SceneSwithDll_example.txt

LIBS += -lws2_32 -luser32

CONFIG += c++11

INCLUDEPATH += $$PWD/osis

CONFIG += static
