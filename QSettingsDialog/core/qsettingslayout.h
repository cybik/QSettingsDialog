#ifndef QSETTINGSLAYOUT_H
#define QSETTINGSLAYOUT_H

#include "qsettingsdialog_global.h"
#include "exceptions.h"
#include <QObject>
#include <QList>
#include <QIcon>
#include <QSharedPointer>
class QSettingsDialogPrivate;
class QSettingsDialog;

class QSettingsLayoutPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsLayout
{
	friend class QSettingsDialogLayout;
	friend class SettingsEntryLayout;
	friend class SettingsGroupLayout;
	friend class SettingsSectionLayout;
	friend class SettingsCategoryLayout;
	friend class SettingsRootLayout;

public:
	enum LayoutType {
		DialogLayout,
		CategoryLayout,
		SectionLayout,
		GroupLayout,
		EntryLayout
	};

	static QSettingsLayout dialogLayout(QSettingsDialog *settingsDialog);

	QString id() const;
	LayoutType layoutType() const;
	bool isNull() const;

	QSettingsDialog *dialog() const;
	QString containerPath() const;

	QSettingsLayout parentContainer() const;

	QString name() const;
	void setName(const QString &name);
	QIcon icon() const;
	void setIcon(const QIcon &icon);
	QString tooltip() const;
	void setTooltip(const QString &tooltip);
	bool isOptional() const;
	void setOptional(bool optional);

	QSettingsLayout defaultElement(bool allowCreateNew = false) const;

	int elementCount() const;
	QSettingsLayout elementAt(int index) const;
	int indexOfElement(const QSettingsLayout &element) const;
	QSettingsLayout createElement(int index,
								  const QString &id,
								  const QString &name = QString(),
								  const QIcon &icon = QIcon(),
								  const QString &tooltip = QString());	
	QSettingsLayout createOptionalElement(int index,
										  const QString &id,
										  const QString &name = QString(),
										  bool optional = false,
										  const QString &tooltip = QString());
	void removeElement(int index);
	void moveElement(int indexFrom, int indexTo);

	void transferElement(int indexFrom, QSettingsLayout targetLayout, int indexTo);

private:
	QSharedPointer<QSettingsLayoutPrivate> d_ptr;

	QSettingsLayout(QSettingsLayoutPrivate *d_ptr);
};

#endif // QSETTINGSLAYOUT_H
