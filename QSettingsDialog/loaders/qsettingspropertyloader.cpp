#include "qsettingspropertyloader.h"
#include <QPointer>

#define d this->d_ptr

class QSettingsPropertyLoaderPrivate
{
public:
	QMetaProperty property;
	QPointer<QObject> object;
	void *gadget;

	QSettingsPropertyLoaderPrivate() :
		property(),
		object(nullptr),
		gadget(nullptr)
	{}
};

QSettingsPropertyLoader::QSettingsPropertyLoader(const char *propertyName, QObject *object) :
	QAsyncSettingsLoader(),
	d_ptr(new QSettingsPropertyLoaderPrivate())
{
	d->object = object;
	auto meta = object->metaObject();
	int index = meta->indexOfProperty(propertyName);
	if(index >= 0)
		d->property = meta->property(index);
}

QSettingsPropertyLoader::QSettingsPropertyLoader(const QMetaProperty &metaProperty, QObject *object) :
	QAsyncSettingsLoader(),
	d_ptr(new QSettingsPropertyLoaderPrivate())
{
	d->object = object;
	d->property = metaProperty;
}

QSettingsPropertyLoader::QSettingsPropertyLoader(const char *propertyName, QMetaObject *metaObject, void *gadget) :
	QAsyncSettingsLoader(),
	d_ptr(new QSettingsPropertyLoaderPrivate())
{
	d->gadget = gadget;
	int index = metaObject->indexOfProperty(propertyName);
	if(index >= 0)
		d->property = metaObject->property(index);
}

QSettingsPropertyLoader::QSettingsPropertyLoader(const QMetaProperty &metaProperty, void *gadget) :
	QAsyncSettingsLoader(),
	d_ptr(new QSettingsPropertyLoaderPrivate())
{
	d->gadget = gadget;
	d->property = metaProperty;
}

QSettingsPropertyLoader::~QSettingsPropertyLoader() {}

QMetaProperty QSettingsPropertyLoader::metaProperty() const
{
	return d->property;
}

bool QSettingsPropertyLoader::isValid() const
{
	return (!d->object.isNull() || d->gadget) &&
			d->property.isValid() &&
			d->property.isReadable();
}

void QSettingsPropertyLoader::loadData()
{
	if(!d->property.isReadable())
		emit loadDone(false, QVariant());

	if(d->object) {
		auto value = d->property.read(d->object);
		emit loadDone(true, value);
	} else if(d->gadget) {
		auto value = d->property.readOnGadget(d->gadget);
		emit loadDone(true, value);
	} else
		emit loadDone(false, QVariant());
}

void QSettingsPropertyLoader::saveData(const QVariant &data)
{
	if(!d->property.isWritable())
		emit saveDone(false);

	if(d->object) {
		auto ok = d->property.write(d->object, data);
		emit saveDone(ok);
	} else if(d->gadget) {
		auto ok = d->property.writeOnGadget(d->gadget, data);
		emit saveDone(ok);
	} else
		emit saveDone(false);
}

void QSettingsPropertyLoader::resetData()
{
	if(!d->property.isResettable())
		emit resetDone(false);

	if(d->object) {
		auto ok = d->property.reset(d->object);
		emit resetDone(ok);
	} else if(d->gadget) {
		auto ok = d->property.resetOnGadget(d->gadget);
		emit resetDone(ok);
	} else
		emit resetDone(false);
}
