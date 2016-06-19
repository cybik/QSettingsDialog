#ifndef QSETTINGSWIDGETDIALOGENGINE_H
#define QSETTINGSWIDGETDIALOGENGINE_H

#include "qsettingsdialog_global.h"
#include "qsettingsdisplayengine.h"
#include "qsettingswidgetfactory.h"
#include "qsettingsentry.h"
#include <QScopedPointer>

class QSettingsWidgetDialogEnginePrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetDialogEngine : public QSettingsDisplayEngine
{
public:
	QSettingsWidgetDialogEngine();
	~QSettingsWidgetDialogEngine();

	QSettingsDisplayInstance *createInstance() override;

	void addFactory(int metatype, QSettingsWidgetFactory *factory);
	template<typename TSettingsWidget>
	void addWidgetType(int metatype);

	QSettingsWidgetBase *createWidget(int metatype,
									  const QSettingsEntry::UiPropertyMap &properties,
									  QWidget *parent) const;

	static void registerGlobalFactory(int metatype, QSettingsWidgetFactory *factory);
	template<typename TSettingsWidget>
	static void registerGlobalWidgetType(int metatype);

private:
	QScopedPointer<QSettingsWidgetDialogEnginePrivate> d_ptr;
};

template<typename TSettingsWidget>
void QSettingsWidgetDialogEngine::addWidgetType(int metatype) {
	this->addFactory(metatype, new GenericSettingsWidgetFactory<TSettingsWidget>());
}

template<typename TSettingsWidget>
void QSettingsWidgetDialogEngine::registerGlobalWidgetType(int metatype) {
	registerGlobalFactory(metatype, new GenericSettingsWidgetFactory<TSettingsWidget>());
}

#endif // QSETTINGSWIDGETDIALOGENGINE_H
