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
CONFIG   += c++11

TEMPLATE = app


SOURCES += \
    ../dsu_osis/calcconnectionthread.cpp \
    osis_unittestmain.cpp \
    osislink_test.cpp \
    osisxml_test.cpp \
    ../dsu_osis/osisdataprovider.cpp \
    ../dsu_osis/osis/event.cpp \
    ../dsu_osis/osis/category.cpp \
    ../dsu_osis/osis/criteria.cpp \
    ../dsu_osis/osis/segment.cpp \
    ../dsu_osis/osis/osisxml.cpp \
    osisxml_recursive.cpp \
    ../dsu_osis/osis/segmentstart.cpp \
    ../dsu_osis/osis/deduction.cpp \
    ../dsu_osis/osis/participant.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dsu_osis/calcconnectionthread.h \
    osis_unittest.h \
    ../dsu_osis/osisdataprovider.h \
    ../dsu_osis/osis/event.h \
    ../dsu_osis/osis/category.h \
    ../dsu_osis/osis/criteria.h \
    ../dsu_osis/osis/segment.h \
    ../dsu_osis/osis/osisxml.h \
    ../dsu_osis/osis/segmentstart.h \
    ../dsu_osis/osis/deduction.h \
    ../dsu_osis/osis/participant.h

DISTFILES += \
    data/seg_run_jdg.xml \
    data/seg_run_clr.xml \
    data/event.xml \
    data/seg_start.xml \
    data/event_clear.xml
