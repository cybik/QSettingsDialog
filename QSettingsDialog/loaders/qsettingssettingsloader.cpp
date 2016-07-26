#include "qsettingssettingsloader.h"

#define d this->d_ptr

class QSettingsSettingsLoaderPrivate
{
public:
	QSettingsSettingsLoaderPrivate(QSettings *settings, const QString &key, const QVariant &defaultValue, bool own);
	~QSettingsSettingsLoaderPrivate();

	QSettings *settings;
	bool deleteSettings;
	QString key;
	QVariant defaultValue;
};

QSettingsSettingsLoader::QSettingsSettingsLoader(const QString &key, const QVariant &defaultValue) :
	d_ptr(new QSettingsSettingsLoaderPrivate(new QSettings(), key, defaultValue, true))
{}

QSettingsSettingsLoader::QSettingsSettingsLoader(QSettings *settings, const QString &key, const QVariant &defaultValue, bool ownSettings) :
	d_ptr(new QSettingsSettingsLoaderPrivate(settings, key, defaultValue, ownSettings))
{}

QSettingsSettingsLoader::~QSettingsSettingsLoader() {}


bool QSettingsSettingsLoader::load(QVariant &data, bool &userEdited)
{
	if(!d->settings)
		return false;
	data = d->settings->value(d->key);
	userEdited = d->settings->contains(d->key);
	return true;
}

bool QSettingsSettingsLoader::save(const QVariant &data)
{
	if(!d->settings)
		return false;
	d->settings->setValue(d->key, data);
	return true;
}

bool QSettingsSettingsLoader::reset()
{
	if(!d->settings)
		return false;
	d->settings->remove(d->key);
	return true;
}

QHash<QString, QSettingsSettingsLoader *> QSettingsSettingsLoader::createLoaders(QSettings *settings, const QString &rootKey, bool recursive)
{
	if(!rootKey.isEmpty())
		settings->beginGroup(rootKey);

	auto resMap = createLoadersImpl(settings, rootKey, recursive);

	if(!rootKey.isEmpty())
		settings->endGroup();
	return resMap;
}

QHash<QString, QSettingsSettingsLoader *> QSettingsSettingsLoader::createLoadersImpl(QSettings *settings, const QString &rootKey, bool recursive)
{
	auto beginBase = rootKey.isEmpty() ? QString() : rootKey + QLatin1Char('/');
	QHash<QString, QSettingsSettingsLoader *> resMap;

	foreach(auto key, settings->childKeys())
		resMap.insert(beginBase + key, new QSettingsSettingsLoader(settings, beginBase + key));

	if(recursive) {
		foreach(auto group, settings->childGroups()) {
			auto newKey = beginBase + group;
			settings->beginGroup(rootKey);
			resMap.unite(createLoadersImpl(settings, newKey, true));
			settings->endGroup();
		}
	}

	return resMap;
}



QSettingsSettingsLoaderPrivate::QSettingsSettingsLoaderPrivate(QSettings *settings, const QString &key, const QVariant &defaultValue, bool own) :
	settings(settings),
	deleteSettings(own),
	key(key),
	defaultValue(defaultValue)
{}

QSettingsSettingsLoaderPrivate::~QSettingsSettingsLoaderPrivate()
{
	if(this->deleteSettings)
		this->settings->deleteLater();
}
