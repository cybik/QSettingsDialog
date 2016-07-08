#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T16:00:06
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EngineTest
TEMPLATE = app

SOURCES += main.cpp \
    testentry.cpp \
    delayedtestentry.cpp \
	swidget.cpp

HEADERS += \
    testentry.h \
    delayedtestentry.h \
    swidget.h

include(../loadLib.pri)
