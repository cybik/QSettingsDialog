#ifndef QSETTINGSWIDGETDIALOGENGINE_H
#define QSETTINGSWIDGETDIALOGENGINE_H

#include "qsettingsdialog_global.h"
#include "qsettingsdisplayengine.h"
#include "qsettingswidgetfactory.h"
#include <QScopedPointer>

class QSettingsWidgetDialogEnginePrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetDialogEngine : public QSettingsDisplayEngine
{
public:
	QSettingsWidgetDialogEngine();
	~QSettingsWidgetDialogEngine();

	QSettingsDisplayInstance *createInstance() override;

	void addFactory(int metatype, QSettingsWidgetFactory *factory);
	template<typename TFactory>
	void addFactory(int metatype);

	QSettingsWidgetBase *createWidget(int metatype, QWidget *parent) const;

	static void registerGlobalFactory(int metatype, QSettingsWidgetFactory *factory);
	template<typename TFactory>
	static void registerGlobalFactory(int metatype);

private:
	QScopedPointer<QSettingsWidgetDialogEnginePrivate> d_ptr;
};

template<typename TFactory>
void QSettingsWidgetDialogEngine::addFactory(int metatype) {
	this->addFactory(metatype, new TFactory());
}

template<typename TFactory>
void QSettingsWidgetDialogEngine::registerGlobalFactory(int metatype) {
	registerGlobalFactory(metatype, new TFactory());
}

#endif // QSETTINGSWIDGETDIALOGENGINE_H
