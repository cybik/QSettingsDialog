TEMPLATE = subdirs

SUBDIRS += \
    QSettingsDialog \
    Demo

Demo.depends += QSettingsDialog
