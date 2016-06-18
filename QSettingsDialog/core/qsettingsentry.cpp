#include "qsettingsentry.h"

#define d this->d_ptr

class QSettingsEntryPrivate
{
public:
	inline QSettingsEntryPrivate(int metatype, QSettingsLoader *loader) :
		metatype(metatype),
		loader(loader),
		name(),
		optional(),
		tooltip()
#ifndef QT_NO_DEBUG
		,refCounter(0)
#endif
	{}

	const int metatype;
	QScopedPointer<QSettingsLoader> loader;

	QString name;
	bool optional;
	QString tooltip;

#ifndef QT_NO_DEBUG
	int refCounter;
#endif
};

QSettingsEntry::QSettingsEntry(int metatype, QSettingsLoader *loader) :
	d_ptr(new QSettingsEntryPrivate(metatype, loader))
{}

QSettingsEntry::~QSettingsEntry()
{
#ifndef QT_NO_DEBUG
	Q_ASSERT_X(d->refCounter == 0, Q_FUNC_INFO, "settings entry destroyed with active loaders!");
#endif
}

QString QSettingsEntry::entryName() const
{
	return d->name;
}

void QSettingsEntry::setEntryName(const QString &name)
{
	d->name = name;
}

bool QSettingsEntry::isOptional() const
{
	return d->optional;
}

void QSettingsEntry::setOptional(bool optional)
{
	d->optional = optional;
}

QString QSettingsEntry::tooltip() const
{
	return d->tooltip;
}

void QSettingsEntry::setTooltip(const QString &tooltip)
{
	d->tooltip = tooltip;
}

int QSettingsEntry::metatype() const
{
	return d->metatype;
}

QSettingsLoader *QSettingsEntry::getLoader()
{
#ifndef QT_NO_DEBUG
	d->refCounter++;
#endif
	return d->loader.data();
}

void QSettingsEntry::freeLoader(QSettingsLoader *)
{
#ifndef QT_NO_DEBUG
	d->refCounter--;
#endif
}
