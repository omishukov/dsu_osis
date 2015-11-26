#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T13:49:45
#
#-------------------------------------------------

QT       += testlib
QT       += network

QT       -= gui

TARGET = osis_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    ../dsu_osis/calcconnectionthread.cpp \
    osis_unittestmain.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dsu_osis/calcconnectionthread.h \
    osis_unittest.h
