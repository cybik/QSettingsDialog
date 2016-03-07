#ifndef QSETTINGSCATEGORY_H
#define QSETTINGSCATEGORY_H

#include "qsettingsdialog_global.h"
#include <QString>
#include <QIcon>
#include <QList>
class QSettingsSection;
class QSettingsGroup;
class QListWidgetItem;
class QTabWidget;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsCategory
{
	friend class QSettingsDialog;
	friend class QSettingsDialogPrivate;

public:
	QString name() const;
	QIcon icon() const;
	QString toolTip() const;

	void setName(const QString &name);
	void setIcon(const QIcon &icon);
	void setToolTip(const QString &toolTip);

	QList<QSettingsSection*> sections(bool includeDefault = false) const;
	QSettingsSection *sectionAt(int index) const;
	int sectionIndex(QSettingsSection *section) const;

	QSettingsSection *insertSection(int index, const QString &name, const QIcon &icon = QIcon());
	inline QSettingsSection *addSection(const QString &name, const QIcon &icon = QIcon()) {
		return this->insertSection(this->sects.size(), name, icon);
	}

	void deleteSection(int index);
	bool deleteSection(QSettingsSection *section);

	void moveSection(int from, int to);

	QSettingsSection *defaultSection();
	QSettingsGroup *defaultGroup();

private:
	QListWidgetItem *listEntry;
	QTabWidget *contentWidget;

	QSettingsSection *defaultSect;
	QList<QSettingsSection*> sects;

	QSettingsCategory(QListWidgetItem *listEntry, QTabWidget *contentWidget);
	~QSettingsCategory();
	void updateSectIndexes();

	QSettingsSection *createSection(int index, const QString &name, const QIcon &icon);
};

#endif // QSETTINGSCATEGORY_H
