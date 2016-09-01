#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T13:49:45
#
#-------------------------------------------------

QT       += testlib
QT       += network
QT       += xml

QT       += gui
QT       += widgets

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
    ../dsu_osis/osis/element/event.cpp \
    ../dsu_osis/osis/element/category.cpp \
    ../dsu_osis/osis/element/criteria.cpp \
    ../dsu_osis/osis/element/segment.cpp \
    ../dsu_osis/osis/osisxml.cpp \
    osisxml_recursive.cpp \
    ../dsu_osis/osis/element/segmentstart.cpp \
    ../dsu_osis/osis/element/deduction.cpp \
    ../dsu_osis/osis/element/participant.cpp \
    ../dsu_osis/osis/osisdata.cpp \
    ../dsu_osis/obs/actions.cpp \
    ../dsu_osis/osis/element/action.cpp \
    ../dsu_osis/osis/element/athlete.cpp \
    ../dsu_osis/osis/element/element.cpp \
    ../dsu_osis/osis/element/elementlist.cpp \
    ../dsu_osis/osis/element/isuosis.cpp \
    ../dsu_osis/osis/element/majoritydeduction.cpp \
    ../dsu_osis/osis/element/official.cpp \
    ../dsu_osis/osis/element/performance.cpp \
    ../dsu_osis/osis/element/prfdetails.cpp \
    ../dsu_osis/osis/element/prfranking.cpp \
    ../dsu_osis/osis/element/segmentrunning.cpp \
    ../dsu_osis/osis/element/warmupgroup.cpp \
    ../dsu_osis/isucompetition.cpp \
    obs_settings.cpp \
    ../dsu_osis/obs/sceneinfo.cpp \
    ../dsu_osis/obs/sceneswitcher.cpp \
    obs_timer.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dsu_osis/calcconnectionthread.h \
    osis_unittest.h \
    ../dsu_osis/osis/element/event.h \
    ../dsu_osis/osis/element/category.h \
    ../dsu_osis/osis/element/criteria.h \
    ../dsu_osis/osis/element/segment.h \
    ../dsu_osis/osis/osisxml.h \
    ../dsu_osis/osis/element/segmentstart.h \
    ../dsu_osis/osis/element/deduction.h \
    ../dsu_osis/osis/element/participant.h \
    ../dsu_osis/osis/osisdata.h \
    ../dsu_osis/osis/competitionif.h \
    ../dsu_osis/osis/dataif.h \
    ../dsu_osis/obsosisif.h \
    ../dsu_osis/obs/actions.h \
    ../dsu_osis/osis/element/action.h \
    ../dsu_osis/osis/element/athlete.h \
    ../dsu_osis/osis/element/element.h \
    ../dsu_osis/osis/element/elementlist.h \
    ../dsu_osis/osis/element/isuosis.h \
    ../dsu_osis/osis/element/majoritydeduction.h \
    ../dsu_osis/osis/element/official.h \
    ../dsu_osis/osis/element/performance.h \
    ../dsu_osis/osis/element/prfdetails.h \
    ../dsu_osis/osis/element/prfranking.h \
    ../dsu_osis/osis/element/segmentrunning.h \
    ../dsu_osis/osis/element/warmupgroup.h \
    ../dsu_osis/isucompetition.h \
    ../dsu_osis/obs/sceneinfo.h \
    ../dsu_osis/obs/sceneswitcher.h

DISTFILES += \
    data/seg_run_jdg.xml \
    data/seg_run_clr.xml \
    data/event.xml \
    data/seg_start.xml \
    data/event_clear.xml \
    data/scenes.json \
    data/basic.ini

INCLUDEPATH += \
    $$PWD/../dsu_osis/osis \
    $$PWD/../dsu_osis
