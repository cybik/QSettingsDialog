# QSettingsDialog
A library to easily create a settings dialog for user configurable settings

# Agenda:
+ Engine
  + core mechanisms
  + ui
  + save/load/reset engine
  + exec/show
  + search filter
  + Layout
- dialogui -> extract/refactor from engine
  + move the real ui here
  - make settingsentry to a class
	- with a "type-id" to get the ui element
	- move the settingswidget to the ui
  - encapsulate widget creation into factories for types
  - add factory-manager/dialog creator to the dialog (abstract)
- variant
- properties
- settings
- custom groups
