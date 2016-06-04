#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T21:32:33
#
#-------------------------------------------------

QT       += widgets

TARGET = QSettingsDialog
TEMPLATE = lib

DEFINES += QSETTINGSDIALOG_LIBRARY

HEADERS += qsettingsdialog_global.h \
	qtexception.h

#parts
include(./engine/engine.pri)

SOURCES += \
	qtexception.cpp
