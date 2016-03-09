#ifndef QSETTINGSGROUP_H
#define QSETTINGSGROUP_H

#include "qsettingsdialog_global.h"
#include <QString>
class QGroupBox;
class QFormLayout;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroup
{
	friend class QSettingsSection;

public:
	bool isActivated() const;

	QString name() const;
	bool isOptional() const;

	void setName(const QString &name);
	void setOptional(bool optional);

private:
	QGroupBox *box;
	QWidget *widget;
	QFormLayout *layout;

	QSettingsGroup(QGroupBox *box);
	QSettingsGroup(QWidget *widget);
	~QSettingsGroup();
};

#endif // QSETTINGSGROUP_H
