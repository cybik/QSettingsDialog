#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T14:07:36
#
#-------------------------------------------------

QT       += widgets

TARGET = QSettingsDialog
TEMPLATE = lib

include(C:/C++Libraries/Qt/DialogMaster/dialogmaster.pri)

DEFINES += QSETTINGSDIALOG_LIBRARY

SOURCES += \
	qsettingsdialog.cpp \
    qsettingscategory.cpp \
    displaydialog.cpp

HEADERS += qsettingsdialog_global.h \
	qsettingsdialog.h \
    qsettingsdialog_p.h \
    qsettingscategory.h \
    displaydialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    displaydialog.ui

RESOURCES += \
    qsettingsdialog_res.qrc
