#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T21:32:33
#
#-------------------------------------------------

TEMPLATE = lib
QT       += widgets
CONFIG += c++14

TARGET = QSettingsDialog
VERSION = 0.1.2

win32 {
	QMAKE_TARGET_COMPANY = "Skycoder42"
	QMAKE_TARGET_PRODUCT = "QSettingsDialog"
	QMAKE_TARGET_DESCRIPTION = $$QMAKE_TARGET_PRODUCT

	CONFIG += skip_target_version_ext
} else:mac {
	QMAKE_TARGET_BUNDLE_PREFIX = "com.Skycoder42."
} else:unix {
	QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''
	QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''
	QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/lib\''
}

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
