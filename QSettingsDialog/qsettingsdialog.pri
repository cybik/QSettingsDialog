win32 {
	msvc {
		contains(QT_ARCH, x86_64) {
			CONFIG(release, debug|release): LIBS += -L$$PWD/msvc64/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/msvc64/debug/ -lQSettingsDialog
		} else {
			CONFIG(release, debug|release): LIBS += -L$$PWD/msvc/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/msvc/debug/ -lQSettingsDialog
		}
	} else:win32-g++ {
		CONFIG(release, debug|release): LIBS += -L$$PWD/mingw/release/ -lQSettingsDialog
		else:CONFIG(debug, debug|release): LIBS += -L$$PWD/mingw/debug/ -lQSettingsDialog
	}
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
