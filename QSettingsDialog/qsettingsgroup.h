#ifndef QSETTINGSGROUP_H
#define QSETTINGSGROUP_H

#include "qsettingsdialog_global.h"
#include <QString>
class QSettingsDialogPrivate;
class QSettingsEntry;
class QSettingsWidgetBase;
class QGroupBox;
class QFormLayout;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroup
{
	friend class QSettingsDialog;
	friend class QSettingsDialogPrivate;
	friend class QSettingsSection;

public:
	bool isActivated() const;

	QString name() const;
	bool isOptional() const;

	void setName(const QString &name);
	void setOptional(bool optional);

	QList<QSettingsEntry*> entries() const;
	QSettingsEntry *entryAt(int index) const;
	int entryIndex(QSettingsEntry *entry) const;

	void insertEntry(int index, QSettingsEntry *entry);
	inline void addEntry(QSettingsEntry *entry) {
		this->insertEntry(this->entrs.size(), entry);
	}

	QSettingsEntry *takeEntry(int index);
	bool takeEntry(QSettingsEntry *entry);

	void deleteEntry(int index);
	bool deleteEntry(QSettingsEntry *entry);

	void moveEntry(int from, int to);

private:
	QSettingsDialogPrivate *priv;

	QGroupBox *box;
	QWidget *widget;
	QFormLayout *layout;

	QList<QSettingsEntry *> entrs;

	QSettingsGroup(QGroupBox *box, QSettingsDialogPrivate *priv);
	QSettingsGroup(QWidget *widget, QSettingsDialogPrivate *priv);
	~QSettingsGroup();

	void setActive(bool active);
};

#endif // QSETTINGSGROUP_H
