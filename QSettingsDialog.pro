TEMPLATE = subdirs

SUBDIRS += \
    QSettingsDialog \
    Demo \
    Test

Demo.depends += QSettingsDialog
