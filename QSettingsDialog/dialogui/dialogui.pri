HEADERS +=  \
	$$PWD/qsettingswidget.h \
    $$PWD/qsettingswidgetdialogengine.h \
    $$PWD/qsettingswidgetfactory.h \
    $$PWD/qsettingswidgetfactoryregistry.h \
    $$PWD/qsettingsdialogwidget.h

INCLUDEPATH += $$PWD

include(private.pri)

SOURCES += \
    $$PWD/qsettingsdialogwidget.cpp
