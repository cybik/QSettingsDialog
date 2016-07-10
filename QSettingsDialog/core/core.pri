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
	$$PWD/container_path_syntax.txt \
    $$PWD/grp_core.dox \
    $$PWD/qsettingsloader.dox \
    $$PWD/qsettingsdialog.dox \
    $$PWD/qsettingsentry.dox \
    $$PWD/qsettingslayout.dox

INCLUDEPATH += $$PWD

include(private.pri)
