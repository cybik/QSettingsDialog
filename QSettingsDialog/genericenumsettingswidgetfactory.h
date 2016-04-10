#ifndef GENERICENUMSETTINGSWIDGETFACTORY_H
#define GENERICENUMSETTINGSWIDGETFACTORY_H

#include "qsettingswidget.h"
#include "qsettingsvariantentry.h"
#include <QMetaEnum>

class QSETTINGSDIALOGSHARED_EXPORT GenericEnumSettingsWidgetFactory : public QSettingsWidgetFactory
{
public:
	GenericEnumSettingsWidgetFactory(bool asFlags, bool preferRadioList);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_OVERRIDE;

	virtual int typeId() const = 0;
	virtual QMetaEnum metaEnum() const = 0;

	template <typename EnumType>
	static void registerEnumFactory(bool asFlags = false, bool preferRadioList = false);

private:
	bool asFlags;
	bool preferRadioList;
};

template <typename EnumType>
class GenericEnumSettingsWidgetFactoryImpl : public GenericEnumSettingsWidgetFactory
{
public:
	GenericEnumSettingsWidgetFactoryImpl(bool asFlags = false, bool preferRadioList = false);

	int typeId() const Q_DECL_FINAL;
	QMetaEnum metaEnum() const Q_DECL_FINAL;
};



template <typename EnumType>
void GenericEnumSettingsWidgetFactory::registerEnumFactory(bool asFlags, bool preferRadioList)
{
	GenericEnumSettingsWidgetFactoryImpl<EnumType> *factory = new GenericEnumSettingsWidgetFactoryImpl<EnumType>(asFlags, preferRadioList);
	QSettingsVariantEntry::registerWidgetFactory(factory->typeId(), factory);
}



template <typename EnumType>
GenericEnumSettingsWidgetFactoryImpl<EnumType>::GenericEnumSettingsWidgetFactoryImpl(bool asFlags, bool preferRadioList) :
	GenericEnumSettingsWidgetFactory(asFlags, preferRadioList)
{}

template <typename EnumType>
int GenericEnumSettingsWidgetFactoryImpl<EnumType>::typeId() const
{
	return qMetaTypeId<EnumType>();
}

template <typename EnumType>
QMetaEnum GenericEnumSettingsWidgetFactoryImpl<EnumType>::metaEnum() const
{
	return QMetaEnum::fromType<EnumType>();
}

#endif // GENERICENUMSETTINGSWIDGETFACTORY_H
