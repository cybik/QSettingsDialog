#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QString>
#include <QIcon>
#include <QScopedPointer>
#include "exceptions.h"
#include "qsettingsentry.h"
class QSettingsDialogLayout;

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	friend class QSettingsDialogPrivate;

public:
	explicit QSettingsDialog(QObject *parent = 0);
	~QSettingsDialog();

	QSettingsDialogLayout *layout();

	//container organisation - getters
	QString containerPath() const;
	QString categoryId() const;
	QString sectionId() const;
	QString groupId() const;

	//container organisation - setters
	void setCategory(const QString &id,
					 const QString &name = QString(),
					 const QIcon &icon = QIcon(),
					 const QString &tooltip = QString());
	void setSection(const QString &id,
					const QString &name = QString(),
					const QIcon &icon = QIcon(),
					const QString &tooltip = QString());
	void setGroup(const QString &id,
				  const QString &name = QString(),
				  bool optional = false,
				  const QString &tooltip = QString());

	void setContainer(const QString &containerPath);
	bool removeContainer(const QString &containerPath);

	//entry organisation
	int appendEntry(QSettingsEntry *entry);
	int appendEntry(const QString &containerPath, QSettingsEntry *entry);
	int prependEntry(QSettingsEntry *entry);
	int prependEntry(const QString &containerPath, QSettingsEntry *entry);

	int appendEntryAsGroup(QSettingsEntry *entry);
	int appendEntryAsGroup(const QString &containerPath, QSettingsEntry *entry);
	int prependEntryAsGroup(QSettingsEntry *entry);
	int prependEntryAsGroup(const QString &containerPath, QSettingsEntry *entry);

	QSettingsEntry *getEntry(int id) const;
	QString getEntryPath(int id) const;
	bool removeEntry(int id);

	//helper
	static QString createContainerPath(QString category = QString(),
									   QString section = QString(),
									   QString group = QString());
	QString createContainerPath(QString category = QString(),
								QString section = QString(),
								QString group = QString(),
								bool escapeAll = false);

	static QSettingsDialog *defaultInstance();

public slots:
	void showSettings(QWidget *parentWindow = nullptr);

signals:
	void saved();
	void resetted();

private:
	QScopedPointer<QSettingsDialogPrivate> d_ptr;
};

#endif // QSETTINGSDIALOG_H
