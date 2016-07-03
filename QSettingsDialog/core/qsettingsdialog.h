#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QString>
#include <QIcon>
#include <QScopedPointer>
#include "exceptions.h"
#include "qsettingsentry.h"
class QSettingsDisplayEngine;
class QSettingsContainer;

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	friend class QSettingsDialogPrivate;

public:
	explicit QSettingsDialog(QObject *parent = nullptr);
	explicit QSettingsDialog(QSettingsDisplayEngine *engine, QObject *parent = nullptr);
	~QSettingsDialog();

	QSettingsDisplayEngine *displayEngine() const;
	void setDisplayEngine(QSettingsDisplayEngine *engine);

	//container organisation - getters
	QString containerPath() const;
	QString sectionContainerPath() const;
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
	void unsetGroup();//TODO set with "." instead?

	void setContainer(const QString &containerPath);
	bool removeContainer(const QString &containerPath);

	QSettingsContainer *currentContainer(QObject *parent = nullptr);
	QSettingsContainer *currentContainerAsync(QObject *parent = nullptr);
	QSettingsContainer *currentSectionContainer(QObject *parent = nullptr);
	QSettingsContainer *currentSectionContainerAsync(QObject *parent = nullptr);

	//entry organisation
	int appendEntry(QSettingsEntry *entry);
	int appendEntry(const QString &containerPath, QSettingsEntry *entry);
	int prependEntry(QSettingsEntry *entry);
	int prependEntry(const QString &containerPath, QSettingsEntry *entry);

	QSharedPointer<QSettingsEntry> getEntry(int id) const;
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
	void openSettings(QWidget *parentWindow = nullptr);
	int execSettings(QWidget *parentWindow = nullptr);

signals:
	void saved(bool closed);
	void resetted();
	void canceled();

private:
	QScopedPointer<QSettingsDialogPrivate> d_ptr;
};

#endif // QSETTINGSDIALOG_H
