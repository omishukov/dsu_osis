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
    osisdataprovider.cpp \
    osis/criteria.cpp \
    osis/category.cpp \
    osis/event.cpp \
    osis/osisxml.cpp \
    osis/segment.cpp \
    osis/segmentstart.cpp \
    osis/deduction.cpp \
    osis/participant.cpp \
    osis/osisdata.cpp \
    isucompetition.cpp

HEADERS  += mainwindow.h \
    calcconnectionthread.h \
    osisdataif.h \
    osisdataprovider.h \
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
    isucompetition.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md \
    LICENSE.txt

LIBS += -lws2_32

CONFIG += static
