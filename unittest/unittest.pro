#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T13:49:45
#
#-------------------------------------------------

QT       += testlib
QT       += network
QT       += xml

QT       -= gui

TARGET = osis_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    ../dsu_osis/calcconnectionthread.cpp \
    osis_unittestmain.cpp \
    osislink_test.cpp \
    osisxml_test.cpp \
    ../dsu_osis/osisdataprovider.cpp \
    ../dsu_osis/event.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dsu_osis/calcconnectionthread.h \
    osis_unittest.h \
    ../dsu_osis/osisdataprovider.h \
    ../dsu_osis/event.h

DISTFILES += \
    data/seg_run_jdg.xml \
    data/seg_run_clr.xml \
    data/event.xml
