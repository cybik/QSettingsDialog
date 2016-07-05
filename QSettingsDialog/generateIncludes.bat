:: This file contains all public include files, ordered by category. These are all headers, that are within the submodules and not part of a private.pri file:
:: Argument 1: out path
:: Working Directory: QSettingsDialog library root path 21
@echo off
mkdir %1

:: --- core ---
xcopy .\core\exceptions.h %1\* /y
xcopy .\core\qsettingsdialog.h %1\* /y
xcopy .\core\qsettingsentry.h %1\* /y
xcopy .\core\qsettingsloader.h %1\* /y
xcopy .\core\qsettingsloaderentry.h %1\* /y
xcopy .\core\qsettingscontainer.h %1\* /y
xcopy .\core\qasyncsettingscontainer.h %1\* /y
xcopy .\core\qsettingslayout.h %1\* /y
xcopy .\core\qsettingsdisplayengine.h %1\* /y

:: --- dialogui ---
xcopy .\dialogui\qsettingswidgetdialogengine.h %1\* /y
xcopy .\dialogui\qsettingswidget.h %1\* /y
xcopy .\dialogui\qsettingswidgetfactory.h %1\* /y
xcopy .\dialogui\qsettingswidgetfactoryregistry.h %1\* /y
xcopy .\dialogui\qsettingsdialogwidget.h %1\* /y
xcopy .\dialogui\qsettingsgroupwidget.h %1\* /y
xcopy .\dialogui\qsettingsgroupwidgetfactory.h %1\* /y

:: --- loaders ---
xcopy .\loaders\qsettingspropertyloader.h %1\* /y
xcopy .\loaders\qsettingspropertyentry.h %1\* /y
xcopy .\loaders\qsettingssettingsloader.h %1\* /y

:: --- variantwidgets ---
xcopy .\variantwidgets\variantwidgetsregistrator.h %1\* /y
xcopy .\variantwidgets\qsettingsextendedtypes.h %1\* /y
