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

#use this to set the defaults for the variant widgets. See qsettingsdialog_global.cpp
DEFINES += "VARIANT_WIDGETS_AUTOLOAD=0x1111"

HEADERS += qsettingsdialog_global.h \
	qtexception.h

SOURCES += \
	qtexception.cpp \
    qsettingsdialog_global.cpp

RESOURCES += \
    qsettingsdialog_res.qrc

DISTFILES += \
	$$PWD/classmodel.qmodel \
    qsettingsdialog.pri \
    generateIncludes.bat

include(./submodules/submodules.pri)
#parts
include(./core/core.pri)
include(./dialogui/dialogui.pri)
include(./variantwidgets/variantwidgets.pri)
include(./loaders/loaders.pri)
