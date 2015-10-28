#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T13:49:45
#
#-------------------------------------------------

QT       += testlib
QT       += network

QT       -= gui

TARGET = tst_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unittesttest.cpp \
    ../dsu_osis/calcconnectionthread.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dsu_osis/calcconnectionthread.h
