#ifndef QSETTINGSDIALOGLAYOUT_H
#define QSETTINGSDIALOGLAYOUT_H

#include "qsettingsdialog_global.h"
#include "exceptions.h"
#include <QObject>
#include <QList>
#include <QIcon>
#include <QSharedPointer>
class QSettingsDialogPrivate;
class QSettingsDialog;

class QSettingsContainerLayout;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialogLayout : public QObject
{
	Q_OBJECT
public:
	enum LayoutType {
		DialogLayout,
		CategoryLayout,
		SectionLayout,
		GroupLayout
	};
	Q_ENUM(LayoutType)

	explicit QSettingsDialogLayout(QSettingsDialog *settingsDialog, QObject *parent = 0);

	QSettingsContainerLayout dialogLayout() const;

private:
	QSettingsDialogPrivate *dialog;
};

class QSettingsContainerLayoutPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsContainerLayout
{
	friend class QSettingsDialogLayout;
	friend class SettingsGroupLayout;
	friend class SettingsSectionLayout;
	friend class SettingsCategoryLayout;
	friend class SettingsRootLayout;

public:
	QString id() const;
	QSettingsDialogLayout::LayoutType layoutType() const;
	bool isNull() const;

	QString name() const;
	void setName(const QString &name);
	QIcon icon() const;
	void setIcon(const QIcon &icon);
	QString tooltip() const;
	void setTooltip(const QString &tooltip);
	bool isOptional() const;
	void setOptional(bool optional);

	QSettingsContainerLayout defaultElement() const;

	int elementCount() const;
	QSettingsContainerLayout elementAt(int index) const;
	int indexOfElement(const QSettingsContainerLayout &element) const;
	QSettingsContainerLayout createElement(int index,
										   const QString &id,
										   const QString &name = QString(),
										   bool optional = false,
										   const QString &tooltip = QString());
	QSettingsContainerLayout createElement(int index,
										   const QString &id,
										   const QString &name = QString(),
										   const QIcon &icon = QIcon(),
										   const QString &tooltip = QString());
	void removeElement(int index);
	void moveElement(int indexFrom, int indexTo);

private:
	QSharedPointer<QSettingsContainerLayoutPrivate> d_ptr;

	QSettingsContainerLayout(QSettingsContainerLayoutPrivate *d_ptr);
};

#endif // QSETTINGSDIALOGLAYOUT_H
