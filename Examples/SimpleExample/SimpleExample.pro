#-------------------------------------------------
#
# Project created by QtCreator 2016-07-04T21:07:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleExample
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
