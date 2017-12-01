SOURCES += \
    main.cpp \
    ui/userinterface.cpp \
    ui/ipconnectui.cpp \
    configuration.cpp \
    tracelog.cpp \
    link/osislink.cpp \
    link/linkif.cpp \
    link/obslink.cpp \
    osis/dataqueue.cpp \
    link/linkbase.cpp \
    ui/calcfsstatusui.cpp \
    osis/parser.cpp

TEMPLATE = app
TARGET = name_of_the_app

QT  = core gui
QT += network
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    ui/userinterface.h \
    ui/ipconnectui.h \
    configuration.h \
    link/osislink.h \
    link/linkif.h \
    link/obslink.h \
    ui/uilinkif.h \
    osis/dataqueue.h \
    link/linkbase.h \
    ui/calcfsstatusui.h \
    osis/parser.h
