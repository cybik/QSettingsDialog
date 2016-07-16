#ifndef QSETTINGSWIDGETDIALOGENGINE_H
#define QSETTINGSWIDGETDIALOGENGINE_H

#include "qsettingsdialog_global.h"
#include "qsettingsdisplayengine.h"
#include "qsettingswidgetfactoryregistry.h"
#include "qsettingsgroupwidgetfactory.h"
#include "qsettingsentry.h"
#include <QScopedPointer>

//! The default engine implementation for the settings dialog @ingroup grp_dialogui
class QSettingsWidgetDialogEnginePrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetDialogEngine : public QSettingsDisplayEngine
{
public:
	//! Creates a new dialog engine
	QSettingsWidgetDialogEngine();
	//! Destructor
	~QSettingsWidgetDialogEngine();

	QSettingsDisplayInstance *createInstance() override;

	//! @intuse Returns the stylesheet to be applied to labels that are a search match
	QString searchStyleSheet() const;

	//! Adds a new settings widget factory with the given id to the default registry
	void addFactory(int displayId, QSettingsWidgetFactory *factory);
	//! Adds a new settings widget factory with the given id
	template<typename TSettingsWidget>
	void addWidgetType(int displayId);

	//! Adds a new group widget factory with the given id
	void addGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory, const UiPropertyMap &properties = UiPropertyMap());
	//! Adds a new group widget factory with the given id
	template<typename TSettingsGroupWidget>
	void addGroupWidgetType(int displayId, const UiPropertyMap &properties = UiPropertyMap());
	//! Creates a clone of a group with a new id and different properties
	void cloneGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties);

	//! @intuse Tries to create a new settings widget for the given id
	QSettingsWidgetBase *createWidget(int displayId,
									  const UiPropertyMap &properties,
									  QWidget *parent) const;
	//! @intuse Tries to create a new group widget for the given id
	QSettingsGroupWidgetBase *createGroupWidget(int displayId,
												QWidget *parent) const;

	//! Adds a new settings widget factory with the given id to the default registry
	static void registerGlobalFactory(int displayId, QSettingsWidgetFactory *factory);
	//! Adds a new settings widget factory with the given id to the default registry
	template<typename TSettingsWidget>
	static void registerGlobalWidgetType(int displayId);

	//! Adds a new settings group factory with the given id to the static groups
	static void registerGlobalGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory);
	//! Adds a new settings group factory with the given id to the static groups
	template<typename TSettingsGroupWidget>
	static void registerGlobalGroupWidgetType(int displayId);
	//! Creates a clone of a static group with a new id and different properties
	static void cloneGlobalGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties);

	//! Adds a new factory registry to this dialog
	void addRegistry(QSettingsWidgetFactoryRegistry *registry);
	//! Adds a new factory registry to the static registries
	static void registerGlobalRegistry(QSettingsWidgetFactoryRegistry *registry);

private:
	QScopedPointer<QSettingsWidgetDialogEnginePrivate> d_ptr;
};

template<typename TSettingsWidget>
void QSettingsWidgetDialogEngine::addWidgetType(int displayId) {
	this->addFactory(displayId, new GenericSettingsWidgetFactory<TSettingsWidget>());
}

template<typename TSettingsGroupWidget>
void QSettingsWidgetDialogEngine::addGroupWidgetType(int displayId, const UiPropertyMap &properties) {
	this->addGroupFactory(displayId, new GenericSettingsGroupWidgetFactory<TSettingsGroupWidget>(), properties);
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
