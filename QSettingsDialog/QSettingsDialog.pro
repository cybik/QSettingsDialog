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
include(./core/core.pri)
include(./dialogui/dialogui.pri)

SOURCES += \
	qtexception.cpp

RESOURCES += \
    qsettingsdialog_res.qrc
