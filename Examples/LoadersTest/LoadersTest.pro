#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T14:28:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoadersTest
TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../QSettingsDialog/release/ -lQSettingsDialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../QSettingsDialog/debug/ -lQSettingsDialog
else:unix: LIBS += -L$$OUT_PWD/../../QSettingsDialog/ -lQSettingsDialog

INCLUDEPATH += $$PWD/../../QSettingsDialog
INCLUDEPATH += $$PWD/../../QSettingsDialog/core
INCLUDEPATH += $$PWD/../../QSettingsDialog/dialogui
INCLUDEPATH += $$PWD/../../QSettingsDialog/loaders
DEPENDPATH += $$PWD/../../QSettingsDialog

HEADERS +=
