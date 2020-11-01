TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -luser32 -lshell32 -lgdi32

SOURCES += \
        cball.cpp \
        cballsarray.cpp \
        cballsettingsmonitor.cpp \
        cbrightball.cpp \
        ccoloredball.cpp \
        main.cpp

HEADERS += \
    cball.h \
    cballsarray.h \
    cballsettingsmonitor.h \
    cbrightball.h \
    ccoloredball.h
