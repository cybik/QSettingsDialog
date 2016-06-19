include(../QColorEdit/qcoloredit.pri)
include(../QPathEdit/qpathedit.pri)

HEADERS += \
    $$PWD/settingscheckbox.h \
    $$PWD/variantwidgetsregistrator.h \
    $$PWD/settingsspinbox.h \
    $$PWD/settingslineedit.h \
    $$PWD/settingsdatetimeedit.h \
    $$PWD/settingscoloredit.h \
    $$PWD/settingslistedit.h \
    $$PWD/settingsfontcombobox.h \
    $$PWD/settingskeyedit.h \
    $$PWD/settingsenumcombobox.h \
    $$PWD/settingsflagschecklist.h

SOURCES += \
    $$PWD/settingscheckbox.cpp \
    $$PWD/variantwidgetsregistrator.cpp \
    $$PWD/settingsspinbox.cpp \
    $$PWD/settingslineedit.cpp \
    $$PWD/settingsdatetimeedit.cpp \
    $$PWD/settingscoloredit.cpp \
    $$PWD/settingslistedit.cpp \
    $$PWD/settingsfontcombobox.cpp \
    $$PWD/settingskeyedit.cpp \
    $$PWD/settingsenumcombobox.cpp \
    $$PWD/settingsflagschecklist.cpp

INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/settingslistedit.ui

RESOURCES += \
    $$PWD/qsettingsdialog_variantwidgets_res.qrc
