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
    osis/criteria.cpp \
    osis/category.cpp \
    osis/event.cpp \
    osis/osisxml.cpp \
    osis/segment.cpp \
    osis/segmentstart.cpp \
    osis/deduction.cpp \
    osis/participant.cpp \
    osis/osisdata.cpp \
    isucompetition.cpp \
    osis/majoritydeduction.cpp \
    osis/official.cpp \
    osis/athlete.cpp \
    osis/element/performance.cpp \
    osis/element/element.cpp \
    osis/element/warmupgroup.cpp \
    osis/element/prfranking.cpp \
    osis/element/segmentrunning.cpp \
    osis/element/action.cpp \
    osis/element/prfdetails.cpp

HEADERS  += mainwindow.h \
    calcconnectionthread.h \
    osis/criteria.h \
    osis/category.h \
    osis/segment.h \
    osis/osisxml.h \
    osis/event.h \
    osis/segmentstart.h \
    osis/deduction.h \
    osis/participant.h \
    osis/osisdata.h \
    trace.h \
    isucompetition.h \
    osis/dataif.h \
    osis/competitionif.h \
    osis/majoritydeduction.h \
    osis/official.h \
    osis/athlete.h \
    osis/element/performance.h \
    osis/element/element.h \
    osis/element/warmupgroup.h \
    osis/element/prfranking.h \
    osis/element/segmentrunning.h \
    osis/element/action.h \
    osis/element/prfdetails.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md \
    LICENSE.txt

LIBS += -lws2_32

INCLUDEPATH += $$PWD/osis

CONFIG += static
