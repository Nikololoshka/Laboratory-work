QT += quick quickcontrols2 qml

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cryptoWrapper.cpp \
        database.cpp \
        main.cpp \
        singletonHelper.cpp \
        user.cpp \
        userRepository.cpp

RESOURCES += qml.qrc

LIBS += -luser32 -lshell32 -lgdi32 -lAdvapi32

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# LIBS += -lcrypt32 lAdvapi32

HEADERS += \
    cryptoWrapper.h \
    database.h \
    singletonHelper.h \
    user.h \
    userRepository.h
