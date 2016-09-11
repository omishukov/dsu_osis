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
    ../OsisProxy/dataqueue.cpp

HEADERS  += mainwindow.h \
    ../OsisProxy/isucalclink.h \
    ../OsisProxy/dataqueue.h

FORMS    += mainwindow.ui

INCLUDEPATH += \
    $$PWD/../OsisProxy
