#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T22:12:43
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Buzzer
TEMPLATE = app

SOURCES += main.cpp\
        ui/mainwindow.cpp

HEADERS  += ui/mainwindow.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    resources.qrc


ICON = resources/Question.icns

include(lib/qextserialport/src/qextserialport.pri)

