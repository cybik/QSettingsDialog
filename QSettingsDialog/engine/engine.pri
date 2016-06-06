HEADERS += \
	$$PWD/qsettingsentry.h \
	$$PWD/qsettingsloader.h \
	$$PWD/qsettingswidget.h \
	$$PWD/qsettingsloaderentry.h \
	$$PWD/qsettingsdialog.h \
    $$PWD/qsettingsdialoglayout.h \
    $$PWD/qsettingscontainer.h \
    $$PWD/exceptions.h \
    $$PWD/qcustomsettingsgroup.h

INCLUDEPATH += $$PWD

include(private.pri)

DISTFILES += \
	$$PWD/container_path_syntax.txt
