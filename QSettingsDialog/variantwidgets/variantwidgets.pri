include(../QColorEdit/qcoloredit.pri)

HEADERS += \
    $$PWD/settingscheckbox.h \
    $$PWD/variantwidgetsregistrator.h \
    $$PWD/settingsspinbox.h \
    $$PWD/settingslineedit.h \
    $$PWD/settingsdatetimeedit.h \
    $$PWD/settingscoloredit.h \
    $$PWD/settingslistedit.h

SOURCES += \
    $$PWD/settingscheckbox.cpp \
    $$PWD/variantwidgetsregistrator.cpp \
    $$PWD/settingsspinbox.cpp \
    $$PWD/settingslineedit.cpp \
    $$PWD/settingsdatetimeedit.cpp \
    $$PWD/settingscoloredit.cpp \
    $$PWD/settingslistedit.cpp

INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/settingslistedit.ui

RESOURCES += \
    $$PWD/qsettingsdialog_variantwidgets_res.qrc
