TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -luser32 -lshell32 -lgdi32

SOURCES += \
        main.cpp

DISTFILES += \
    dat.txt
