#ifndef QSETTINGSVARIANTENTRY_H
#define QSETTINGSVARIANTENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsVariantLoader : public QSettingsLoader
{
public:
	typedef QHash<QString, QVariant> PropertyMap;

	virtual int variantTypeID() const = 0;
	virtual PropertyMap widgetProperties() const = 0;
};

class QSettingsWidgetFactory
{
public:
	inline virtual ~QSettingsWidgetFactory() {}

	virtual QSettingsWidgetBase *createWidget(QWidget *parent) = 0;
	virtual void destroyWidget(QSettingsWidgetBase *widget) = 0;
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsVariantEntry : public QSettingsEntry
{
public:
	QSettingsVariantEntry(const QString &entryName, bool isOptional, QSettingsVariantLoader *loader);

	// QSettingsEntry interface
	QString entryName() const Q_DECL_FINAL;
	bool isOptional() const Q_DECL_FINAL;
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_FINAL;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_FINAL;
	QSettingsLoader *getLoader() const Q_DECL_FINAL;

	static void registerWidgetFactory(int variantType, QSettingsWidgetFactory *factory);
	template<typename T>
	static void registerWidgetType(int variantType);

private:
	QString name;
	bool optional;
	QSettingsVariantLoader *loader;
};

// --- Variant type ---

template <class SettingsWidgetClass>
class GenericSettingsWidgetFactory : public QSettingsWidgetFactory
{
public:
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_FINAL {
		return new SettingsWidgetClass(parent);
	}
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_FINAL {
		widget->asWidget()->deleteLater();
	}
};

template<class SettingsWidgetClass>
void QSettingsVariantEntry::registerWidgetType(int variantType)
{
	QSettingsVariantEntry::registerWidgetFactory(variantType,
												 new GenericSettingsWidgetFactory<SettingsWidgetClass>());
}

#endif // QSETTINGSVARIANTENTRY_H
