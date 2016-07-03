#ifndef QSETTINGSCONTAINER_H
#define QSETTINGSCONTAINER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QScopedPointer>
#include "qsettingsentry.h"
#include "exceptions.h"
class QSettingsDialog;
class QSettingsLayout;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsContainer : public QObject
{
	Q_OBJECT

public:
	virtual QSettingsDialog *dialog() const = 0;
	virtual QString containerPath() const = 0;

	virtual int elementCount() const = 0;
	virtual bool isEntry(int index) const = 0;
	virtual int getEntryIndex(int id) const = 0;
	virtual int getEntryId(int index) const = 0;
	virtual QSharedPointer<QSettingsEntry> getEntry(int id) const = 0;
	virtual QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const = 0;

	virtual bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) = 0;

public slots:
	virtual int appendEntry(QSettingsEntry *entry) = 0;
	virtual int prependEntry(QSettingsEntry *entry) = 0;
	virtual int insertEntry(int index, QSettingsEntry *entry) = 0;
	virtual int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) = 0;

	virtual bool removeEntry(int id) = 0;
	virtual bool removeElementFromIndex(int index) = 0;
	virtual void moveElement(int indexFrom, int indexTo) = 0;

protected:
	inline QSettingsContainer(QObject *parent = nullptr) :
		QObject(parent)
	{}

	virtual bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) = 0;
	inline bool doAccept(QSettingsContainer *target, int index, int id, QSharedPointer<QSettingsEntry> entry) {
		return target->acceptEntry(index, id, entry);
	}
};

class QSectionSettingsContainer;
class QGroupSettingsContainerPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QGroupSettingsContainer : public QSettingsContainer
{
	Q_OBJECT

public:
	explicit QGroupSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent = nullptr);
	explicit QGroupSettingsContainer(QSettingsLayout *layout, QObject *parent = nullptr);
	~QGroupSettingsContainer();

	QSettingsDialog *dialog() const override;
	QString containerPath() const override;

	int elementCount() const override;
	bool isEntry(int index) const override;
	int getEntryIndex(int id) const override;
	int getEntryId(int index) const override;
	QSharedPointer<QSettingsEntry> getEntry(int id) const override;
	QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const override;

	bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) override;

	QSectionSettingsContainer *parentSection();
	QSectionSettingsContainer *parentSection(QObject *parent) const;

public slots:
	int appendEntry(QSettingsEntry *entry) override;
	int prependEntry(QSettingsEntry *entry) override;
	int insertEntry(int index, QSettingsEntry *entry) override;
	int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) override;

	bool removeEntry(int id) override;
	bool removeElementFromIndex(int index) override;
	void moveElement(int indexFrom, int indexTo) override;

protected:
	bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) override;

private:
	QScopedPointer<QGroupSettingsContainerPrivate> d_ptr;
};

class QSectionSettingsContainerPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSectionSettingsContainer : public QSettingsContainer
{
	Q_OBJECT

public:
	explicit QSectionSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent = nullptr);
	explicit QSectionSettingsContainer(QSettingsLayout *layout, QObject *parent = nullptr);
	~QSectionSettingsContainer();

	QSettingsDialog *dialog() const override;
	QString containerPath() const override;

	int elementCount() const override;
	bool isEntry(int index) const override;

	int getEntryIndex(int id) const override;
	int getGroupIndex(const QString &id) const;

	QVariant getElementId(int index) const;
	int getEntryId(int index) const override;
	QString getGrouptId(int index) const;

	QSharedPointer<QSettingsEntry> getEntry(int id) const override;
	QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const override;

	bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) override;

	QGroupSettingsContainer *createGroupContainer(const QString &id);
	QGroupSettingsContainer *createGroupContainer(const QString &id, QObject *parent) const;
	QGroupSettingsContainer *createGroupContainerFromIndex(int index);
	QGroupSettingsContainer *createGroupContainerFromIndex(int index, QObject *parent) const;

public slots:
	int appendEntry(QSettingsEntry *entry) override;
	int prependEntry(QSettingsEntry *entry) override;
	int insertEntry(int index, QSettingsEntry *entry) override;
	int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) override;

	void appendGroup(const QString &id,
					 int displayId = 0,
					 const QString &name = QString(),
					 bool optional = false,
					 const QString &tooltip = QString());
	void prependGroup(const QString &id,
					  int displayId = 0,
					  const QString &name = QString(),
					  bool optional = false,
					  const QString &tooltip = QString());
	void insertGroup(int index,
					 const QString &id,
					 int displayId = 0,
					 const QString &name = QString(),
					 bool optional = false,
					 const QString &tooltip = QString());

	bool removeEntry(int id) override;
	bool removeGroup(const QString &id);
	bool removeElementFromIndex(int index) override;
	void moveElement(int indexFrom, int indexTo) override;

protected:
	bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) override;

private:
	QScopedPointer<QSectionSettingsContainerPrivate> d_ptr;
};

#endif // QSETTINGSCONTAINER_H
