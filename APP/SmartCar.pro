#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T20:14:21
#
#-------------------------------------------------

QT       += core gui
QT      += bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

TARGET = SmartCar
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MsgDialog.cpp \
    Bluetooth.cpp \
    NewWindow.cpp \
    Protocol.cpp \
    ControlPanel.cpp \
    QMyPushButton.cpp

HEADERS  += MainWindow.h \
    MsgDialog.h \
    Bluetooth.h \
    NewWindow.h \
    Protocol.h \
    ControlPanel.h \
    QMyPushButton.h

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml

RESOURCES += \
    res.qrc

