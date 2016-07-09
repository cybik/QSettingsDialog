#ifndef QSETTINGSWIDGETDIALOGENGINE_H
#define QSETTINGSWIDGETDIALOGENGINE_H

#include "qsettingsdialog_global.h"
#include "qsettingsdisplayengine.h"
#include "qsettingswidgetfactoryregistry.h"
#include "qsettingsgroupwidgetfactory.h"
#include "qsettingsentry.h"
#include <QScopedPointer>

class QSettingsWidgetDialogEnginePrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetDialogEngine : public QSettingsDisplayEngine
{
public:
	QSettingsWidgetDialogEngine();
	~QSettingsWidgetDialogEngine();

	QSettingsDisplayInstance *createInstance() override;

	QString searchStyleSheet() const;

	void addFactory(int displayId, QSettingsWidgetFactory *factory);
	template<typename TSettingsWidget>
	void addWidgetType(int displayId);

	void addGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory);
	template<typename TSettingsGroupWidget>
	void addGroupWidgetType(int displayId);
	void cloneGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties);

	QSettingsWidgetBase *createWidget(int displayId,
									  const UiPropertyMap &properties,
									  QWidget *parent) const;
	QSettingsGroupWidgetBase *createGroupWidget(int displayId,
												QWidget *parent) const;

	static void registerGlobalFactory(int displayId, QSettingsWidgetFactory *factory);
	template<typename TSettingsWidget>
	static void registerGlobalWidgetType(int displayId);

	static void registerGlobalGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory);
	template<typename TSettingsGroupWidget>
	static void registerGlobalGroupWidgetType(int displayId);
	static void cloneGlobalGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties);

	void addRegistry(QSettingsWidgetFactoryRegistry *registry);
	static void registerGlobalRegistry(QSettingsWidgetFactoryRegistry *registry);

private:
	QScopedPointer<QSettingsWidgetDialogEnginePrivate> d_ptr;
};

template<typename TSettingsWidget>
void QSettingsWidgetDialogEngine::addWidgetType(int displayId) {
	this->addFactory(displayId, new GenericSettingsWidgetFactory<TSettingsWidget>());
}

template<typename TSettingsGroupWidget>
void QSettingsWidgetDialogEngine::addGroupWidgetType(int displayId) {
	this->addGroupFactory(displayId, new GenericSettingsGroupWidgetFactory<TSettingsGroupWidget>());
}

template<typename TSettingsWidget>
void QSettingsWidgetDialogEngine::registerGlobalWidgetType(int displayId) {
	registerGlobalFactory(displayId, new GenericSettingsWidgetFactory<TSettingsWidget>());
}

template<typename TSettingsGroupWidget>
void QSettingsWidgetDialogEngine::registerGlobalGroupWidgetType(int displayId) {
	registerGlobalGroupFactory(displayId, new GenericSettingsGroupWidgetFactory<TSettingsGroupWidget>());
}

#endif // QSETTINGSWIDGETDIALOGENGINE_H
