HEADERS += \
	$$PWD/qsettingsentry.h \
	$$PWD/qsettingsloader.h \
	$$PWD/qsettingsloaderentry.h \
	$$PWD/qsettingsdialog.h \
    $$PWD/qsettingscontainer.h \
    $$PWD/exceptions.h \
	$$PWD/qsettingslayout.h \
	$$PWD/qsettingsdisplayengine.h \
    $$PWD/qasyncsettingscontainer.h

DISTFILES += \
	$$PWD/container_path_syntax.txt

INCLUDEPATH += $$PWD

include(private.pri)
