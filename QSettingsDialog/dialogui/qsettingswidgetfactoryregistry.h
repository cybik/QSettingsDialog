#ifndef QSETTINGSWIDGETFACTORYREGISTRY_H
#define QSETTINGSWIDGETFACTORYREGISTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingswidgetfactory.h"
#include <QSharedPointer>

class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetFactoryRegistry
{
public:
	inline virtual ~QSettingsWidgetFactoryRegistry() {}

	virtual inline int priority() const {
		return 0;
	}
	virtual QSharedPointer<QSettingsWidgetFactory> tryResolve(int displayId) = 0;
};

#endif // QSETTINGSWIDGETFACTORYREGISTRY_H
