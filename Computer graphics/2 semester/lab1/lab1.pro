TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -luser32 -lshell32 -lgdi32

SOURCES += \
        cball.cpp \
        chlimiter.cpp \
        crect.cpp \
        main.cpp

HEADERS += \
    cball.h \
    chlimiter.h \
    crect.h
