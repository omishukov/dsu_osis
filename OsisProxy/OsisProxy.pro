#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T20:30:43
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OsisProxy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    isucalclink.cpp

HEADERS  += mainwindow.h \
    isucalclink.h

FORMS    += mainwindow.ui
