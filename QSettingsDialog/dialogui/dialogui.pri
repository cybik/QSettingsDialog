include(../DialogMaster/dialogmaster.pri)

HEADERS +=  \
	$$PWD/qsettingswidget.h \
    $$PWD/qsettingswidgetdialogengine.h \
    $$PWD/qsettingswidgetfactory.h \
    $$PWD/qsettingswidgetfactoryregistry.h

INCLUDEPATH += $$PWD

include(private.pri)
