SOURCES += \
    main.cpp \
    ui/userinterface.cpp \
    ui/ipconnectui.cpp \
    configuration.cpp

TEMPLATE = app
TARGET = name_of_the_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    ui/userinterface.h \
    ui/ipconnectui.h \
    configuration.h
