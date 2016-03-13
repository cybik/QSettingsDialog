#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T14:07:36
#
#-------------------------------------------------

QT       += widgets
CONFIG *= C++11

TARGET = QSettingsDialog
TEMPLATE = lib

include(C:/C++Libraries/Qt/DialogMaster/dialogmaster.pri)
include(C:/C++Libraries/Qt/QColorEdit/qcoloredit.pri)

DEFINES += QSETTINGSDIALOG_LIBRARY

SOURCES += \
	qsettingsdialog.cpp \
    qsettingscategory.cpp \
    qsettingssection.cpp \
    qsettingsgroup.cpp \
    qsettingsloader.cpp \
    qsettingswidget.cpp \
    qsettingsdialog_p.cpp \
    qsettingsloaderentry.cpp \
    qsettingsvariantentry.cpp

HEADERS += qsettingsdialog_global.h \
	qsettingsdialog.h \
    qsettingsdialog_p.h \
    qsettingscategory.h \
    qsettingssection.h \
    qsettingsgroup.h \
    qsettingsentry.h \
    qsettingsloader.h \
    qsettingswidget.h \
    qsettingsloaderentry.h \
    qsettingsvariantentry.h \
	qsettingsvariantentry_p.h

FORMS += \
    qsettingsdialog.ui

RESOURCES += \
    qsettingsdialog_res.qrc

include(./standardSettingsWidgets/standardSettingsWidgets.pri)
