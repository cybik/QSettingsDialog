#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T14:09:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QSettingsDialog/release/ -lQSettingsDialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QSettingsDialog/debug/ -lQSettingsDialog
else:unix: LIBS += -L$$OUT_PWD/../QSettingsDialog/ -lQSettingsDialog

INCLUDEPATH += $$PWD/../QSettingsDialog
DEPENDPATH += $$PWD/../QSettingsDialog
