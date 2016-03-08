#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T18:57:08
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_categorytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    tst_qsettingsdialog.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_qsettingsdialog.h \
    testglobal.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QSettingsDialog/release/ -lQSettingsDialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QSettingsDialog/debug/ -lQSettingsDialog
else:unix: LIBS += -L$$OUT_PWD/../QSettingsDialog/ -lQSettingsDialog

INCLUDEPATH += $$PWD/../QSettingsDialog
DEPENDPATH += $$PWD/../QSettingsDialog
