CONFIG      += serialport
#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T17:45:27
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += declarative
QT       += webkit
QT       += webkitwidgets
QT       += script
QT       += scripttools

TARGET = test_webkit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myobj.cpp

HEADERS += \
    myobj.h
