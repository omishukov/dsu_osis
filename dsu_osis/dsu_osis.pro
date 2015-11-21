#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T09:55:50
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dsu_osis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calcconnectionthread.cpp \
    osisdataprovider.cpp

HEADERS  += mainwindow.h \
    calcconnectionthread.h \
    osisdataif.h \
    osisdataprovider.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md

LIBS += -lws2_32

CONFIG += static
