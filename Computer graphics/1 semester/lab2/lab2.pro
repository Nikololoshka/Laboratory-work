TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -luser32 -lshell32 -lgdi32

SOURCES += \
        main.cpp
