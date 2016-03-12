#ifndef QSETTINGSSECTION_H
#define QSETTINGSSECTION_H

#include "qsettingsdialog_global.h"
#include <QString>
#include <QIcon>
#include <QList>
class QSettingsDialogPrivate;
class QSettingsGroup;
class QTabBar;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsSection
{
	friend class QSettingsCategory;

public:
	QString name() const;
	QIcon icon() const;

	void setName(const QString &name);
	void setIcon(const QIcon &icon);

	QList<QSettingsGroup*> groups(bool includeDefault = false) const;
	int groupCount() const;
	QSettingsGroup *groupAt(int index) const;
	int groupIndex(QSettingsGroup *group) const;

	QSettingsGroup *insertGroup(int index, const QString &name, bool optional = false);
	inline QSettingsGroup *addGroup(const QString &name, bool optional = false) {
		return this->insertGroup(this->grps.size(), name, optional);
	}

	void deleteGroup(int index);
	bool deleteGroup(QSettingsGroup *group);

	void moveGroup(int from, int to);
	void transferGroup(int from, QSettingsSection *target, int to);

	QSettingsGroup *defaultGroup();
	bool hasDefaultGroup() const;

private:
	QSettingsDialogPrivate *priv;

	QTabBar *tabBar;
	int tabIndex;
	QWidget *contentWidget;

	QSettingsGroup *defaultGrp;
	QList<QSettingsGroup*> grps;

	QSettingsSection(QTabBar *tabBar, int tabIndex, QWidget *contentWidget, QSettingsDialogPrivate *priv);
	~QSettingsSection();
	void updateIndex(int tabIndex);
};

#endif // QSETTINGSSECTION_H
