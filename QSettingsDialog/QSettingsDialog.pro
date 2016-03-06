#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T14:07:36
#
#-------------------------------------------------

QT       += widgets

TARGET = QSettingsDialog
TEMPLATE = lib

DEFINES += QSETTINGSDIALOG_LIBRARY

include(./public.pri)

SOURCES += qsettingsdialog.cpp

HEADERS +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}
