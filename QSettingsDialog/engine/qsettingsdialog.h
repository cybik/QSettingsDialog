#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QString>
#include <QIcon>
#include "qtexception.h"
#include "qsettingsentry.h"

class QSETTINGSDIALOGSHARED_EXPORT InvalidContainerPathException : public QtException
{
public:
	InvalidContainerPathException();
};

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	friend class QSettingsDialogPrivate;

public:
	explicit QSettingsDialog(QObject *parent = 0);

	//container organisation - getters
	QString containerPath() const;
	QString categoryId() const;
	QString sectionId() const;
	QString groupId() const;

	QString name(const QString &containerPath) const;
	QIcon icon(const QString &containerPath) const;
	QString tooltip(const QString &containerPath) const;
	bool isOptional(const QString &groupPath) const;

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
	void moveContainer(const QString &fromPath,
					   const QString &toPath);

	void setName(const QString &containerPath, const QString &name);
	void setIcon(const QString &containerPath, const QIcon &icon);
	void setTooltip(const QString &containerPath, const QString &tolltip);
	void setOptional(const QString &groupPath, bool optional);
	void setOptional(bool optional);

	//entry organisation
	int addEntry(QSettingsEntry *entry);
	int addEntry(const QString &containerPath, QSettingsEntry *entry);
	QSettingsEntry *getEntry(int id) const;
	bool removeEntry(int id);
	void moveEntry(int id, const QString &targetContainerPath);

	//helper
	static QString createContainerPath(const QString &category = QString(),
									   const QString &section = QString(),
									   const QString &group = QString(),
									   bool escapeAll = false);

	static QSettingsDialog *defaultInstance();

public slots:
	void showSettings(QWidget *parentWindow = nullptr);

signals:
	void saved();
	void resetted();

private:
	QSettingsDialogPrivate *d_ptr;
};

#endif // QSETTINGSDIALOG_H
