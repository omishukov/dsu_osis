#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T20:30:43
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OsisProxy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    isucalclink.cpp \
    dataqueue.cpp \
    osisdataproxy.cpp \
    ../dsu_osis/osis/osisdata.cpp \
    ../dsu_osis/osis/element/action.cpp \
    proxyserver.cpp \
    websocketserver.cpp

HEADERS  += mainwindow.h \
    isucalclink.h \
    dataqueue.h \
    osisdataproxy.h \
    ../dsu_osis/osis/osisdata.h \
    ../dsu_osis/osis/element/action.h \
    proxyserver.h \
    websocketserver.h

FORMS    += mainwindow.ui

INCLUDEPATH += \
    $$PWD/../dsu_osis/osis \
    $$PWD/../dsu_osis

RC_ICONS = ../OsisSwitcher/danskate.ico

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags)
GIT_VERSION ~= s/'[A-Z]'/""

DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

VERSION = $$GIT_VERSION
VERSION ~= s/\.\d+\.[a-f0-9]{6,}//
