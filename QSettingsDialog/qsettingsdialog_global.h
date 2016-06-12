#ifndef QSETTINGSDIALOGENGINE_GLOBAL_H
#define QSETTINGSDIALOGENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QSETTINGSDIALOG_LIBRARY)
#  define QSETTINGSDIALOGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QSETTINGSDIALOGSHARED_EXPORT Q_DECL_IMPORT
#endif

#define outParam &

#ifdef QT_NO_DEBUG
#define safe_cast static_cast
#else
template <typename TTo, typename TFrom>
inline TTo safeCast(TFrom from) {
	Q_ASSERT_X(dynamic_cast<TTo>(from), "", "static cast not possible! Dynamic cast assertion failed!");
	return static_cast<TTo>(from);
}
#define safe_cast safeCast

#endif

#endif // QSETTINGSDIALOGENGINE_GLOBAL_H
