SOURCES += \
	$$PWD/qsettingsloader.cpp \
	$$PWD/qsettingswidget.cpp \
	$$PWD/qsettingsdialog.cpp

HEADERS += \
	$$PWD/qsettingsentry.h \
	$$PWD/qsettingsloader.h \
	$$PWD/qsettingswidget.h \
	$$PWD/qsettingsloaderentry.h \
	$$PWD/qsettingsdialog.h

INCLUDEPATH += $$PWD

include(private.pri)

DISTFILES += \
    $$PWD/container_path_syntax.txt
