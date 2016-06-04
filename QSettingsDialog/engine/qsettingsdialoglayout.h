#ifndef QSETTINGSDIALOGLAYOUT_H
#define QSETTINGSDIALOGLAYOUT_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QList>
#include <QIcon>
class QSettingsDialogPrivate;
class QSettingsDialog;

template <class SettingsLayout>
class QSETTINGSDIALOGSHARED_EXPORT LayoutList
{
	friend class QSettingsDialogLayout;
public:
	int size() const;

	void move(int indexFrom, int indexTo);
	SettingsLayout at(int index) const;
	int indexOf(const SettingsLayout &element) const;

	SettingsLayout &operator[](int index);

private:
	QList<SettingsLayout> dataList;
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroupLayout
{
	friend class QSettingsSectionLayout;
public:
	const QString &id;

	QString &name;
	QString &tooltip;
	bool &isOptional;

	//TODO createContainer

private:
	QSettingsGroupLayout(const QString &id,
						 QString &name,
						 QString &tooltip,
						 bool &isOptional);
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsSectionLayout
{
	friend class QSettingsCategoryLayout;
public:
	const QString &id;

	QString &name;
	QIcon &icon;
	QString &tooltip;

	QSettingsGroupLayout defaultGroup;
	LayoutList<QSettingsGroupLayout> groups;

	QSettingsGroupLayout createGroup(int index,
									 const QString &id,
									 const QString &name = QString(),
									 bool optional = false,
									 const QString &tooltip = QString());
	void removeGroup(int index);

private:
	QSettingsSectionLayout(const QString &id,
						   QString &name,
						   QIcon &icon,
						   QString &tooltip);
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsCategoryLayout
{
	friend class QSettingsDialogLayout;
public:
	const QString &id;

	QString &name;
	QIcon &icon;
	QString &tooltip;

	QSettingsSectionLayout defaultSection;
	LayoutList<QSettingsSectionLayout> sections;

	QSettingsGroupLayout createSection(int index,
									   const QString &id,
									   const QString &name = QString(),
									   const QIcon &icon = QIcon(),
									   const QString &tooltip = QString());
	void removeSection(int index);

private:
	QSettingsCategoryLayout(const QString &id,
							QString &name,
							QIcon &icon,
							QString &tooltip);
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialogLayout : public QObject
{
	Q_OBJECT
public:
	explicit QSettingsDialogLayout(QSettingsDialog *settingsDialog, QObject *parent = 0);

	QSettingsCategoryLayout defaultCategory;
	LayoutList<QSettingsCategoryLayout> categories;

	QSettingsCategoryLayout createCategory(int index,
										   const QString &id,
										   const QString &name = QString(),
										   const QIcon &icon = QIcon(),
										   const QString &tooltip = QString());
	void removeSecCategory(int index);
private:
	QSettingsDialogPrivate *dialog;
};

// --------------------------- IMPLEMENTATION --------------------------

template <class SettingsLayout>
int LayoutList<SettingsLayout>::size() const {
	return this->dataList.size();
}

template <class SettingsLayout>
void LayoutList<SettingsLayout>::move(int indexFrom, int indexTo) {
	this->dataList.move(indexFrom, indexTo);
}

template <class SettingsLayout>
typename SettingsLayout LayoutList<SettingsLayout>::at(int index) const {
	return this->dataList.at(index);
}

template <class SettingsLayout>
int LayoutList<SettingsLayout>::indexOf(const SettingsLayout &element) const {
	return this->dataList.indexOf(element);
}

template <class SettingsLayout>
typename SettingsLayout &LayoutList<SettingsLayout>::operator[](int index) {
	return this->dataList[index];
}

#endif // QSETTINGSDIALOGLAYOUT_H
