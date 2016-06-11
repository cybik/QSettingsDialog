#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T16:00:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EngineTest
TEMPLATE = app


SOURCES += main.cpp \
    testentry.cpp \
    delayedtestentry.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../QSettingsDialog/release/ -lQSettingsDialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../QSettingsDialog/debug/ -lQSettingsDialog
else:unix: LIBS += -L$$OUT_PWD/../../QSettingsDialog/ -lQSettingsDialog

INCLUDEPATH += $$PWD/../../QSettingsDialog
INCLUDEPATH += $$PWD/../../QSettingsDialog/engine
DEPENDPATH += $$PWD/../../QSettingsDialog

HEADERS += \
    testentry.h \
    delayedtestentry.h \
    swidget.h
