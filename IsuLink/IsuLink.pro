#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T15:42:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IsuLink
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainisulink.cpp

HEADERS  += mainisulink.h

FORMS    += mainisulink.ui

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags)
GIT_VERSION ~= s/v/""
GIT_VERSION ~= s/g/""
GIT_VERSION ~= s/b/""
GIT_VERSION ~= s/d/""
GIT_VERSION ~= s/f/""

DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

VERSION = $$GIT_VERSION
VERSION ~= s/\.\d+\.[a-f0-9]{6,}//
