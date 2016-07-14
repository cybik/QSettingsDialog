HEADERS +=  \
	$$PWD/qsettingswidget.h \
    $$PWD/qsettingswidgetdialogengine.h \
    $$PWD/qsettingswidgetfactory.h \
    $$PWD/qsettingswidgetfactoryregistry.h \
    $$PWD/qsettingsdialogwidget.h \
    $$PWD/qsettingsgroupwidget.h \
    $$PWD/qsettingsgroupwidgetfactory.h

INCLUDEPATH += $$PWD

include(private.pri)

DISTFILES += \
    $$PWD/grp_dialogui.dox \
    $$PWD/qsettingswidget.dox
