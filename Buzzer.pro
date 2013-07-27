#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T22:12:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Buzzer
TEMPLATE = app

include(lib/qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc


