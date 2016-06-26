#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T21:32:33
#
#-------------------------------------------------

QT       += widgets
CONFIG += c++14

TARGET = QSettingsDialog
TEMPLATE = lib

DEFINES += QSETTINGSDIALOG_LIBRARY

HEADERS += qsettingsdialog_global.h \
	qtexception.h

SOURCES += \
	qtexception.cpp \
    qsettingsdialog_global.cpp

RESOURCES += \
    qsettingsdialog_res.qrc

DISTFILES += \
	$$PWD/classmodel.qmodel

include(./submodules/submodules.pri)
#parts
include(./core/core.pri)
include(./dialogui/dialogui.pri)
include(./variantwidgets/variantwidgets.pri)
