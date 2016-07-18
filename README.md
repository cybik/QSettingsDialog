# QSettingsDialog
[![BSD3 License](https://img.shields.io/badge/license-BSD3-blue.svg?style=flat)](https://opensource.org/licenses/BSD-3-Clause)

A Qt library to easily create a settings dialog for user configurable settings.

Github repository: https://github.com/Skycoder42/QSettingsDialog

## Main Features
The settings dialog provides a number of classes to create simple to highly customizable settings dialogs. It provides simple, general interfaces to easily create a normal settings dialog, as well as many mechanisms to make it highly customizable and easily extendable.
The library is split into four logical modules, based on concern.

### Core-Module
The core module is responsible for the definition of the base classes and the managemant behind the dialog. It's main features are:
- A central class for simple dialog creation
- Advanced classes to control the appeareance and allow encapsualted and threaded access to the dialog
- Abstraction from the actual ui, by using a defined logical structure of entry organization
- Provides interfaces to allow a completly customized UI

### Dialog-UI-Modle
This module provides the standard widgets based dialog ui, as well the interfaces needed to customize appeareance and possible edit widgets:
- Generic dialog ui, for all 3 Desktop platforms
- Interfaces for custom entry groups
- Interfaces for custom edit widgets

### Variantwidgets-Module
This module contains a collection of default and advanced edit widgets for standard types and others:
- Seperation of different edit groups
- Supports all basic datatypes, enums, flags and a few specialized custom types

### Loaders-Module
This module contains a number of custom settings datasources, to load settings entries from:
- Provides loading from QSettings
- Provides loading from QObject properties
