#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QScopedPointer>
#include <QIcon>
class QSettingsCategory;
class QSettingsSection;
class QSettingsGroup;

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(QSettingsDialog)

	Q_PROPERTY(QSize categoryIconSize READ categoryIconSize WRITE setCategoryIconSize RESET resetCategoryIconSize)

public:
	QSettingsDialog(QObject *parent = Q_NULLPTR);
	~QSettingsDialog();

	QList<QSettingsCategory*> categories(bool includeDefault = false) const;
	int categoryCount() const;
	QSettingsCategory *categoryAt(int index) const;
	int categoryIndex(QSettingsCategory *category) const;

	QSettingsCategory *insertCategory(int index, const QString &name, const QIcon &icon = QIcon(), const QString &toolTip = QString());
	QSettingsCategory *addCategory(const QString &name, const QIcon &icon = QIcon(), const QString &toolTip = QString());

	void deleteCategory(int index);
	bool deleteCategory(QSettingsCategory *category);

	void moveCategory(int from, int to);

	QSettingsCategory *defaultCategory();
	QSettingsSection *defaultSection();
	QSettingsGroup *defaultGroup();
	bool hasDefaultCategory() const;

	QSize categoryIconSize() const;

public slots:
	void showDialog();

	void setCategoryIconSize(QSize categoryIconSize);
	void resetCategoryIconSize();

private slots:
	void loadDone(const QVariant &data, bool isUser);
	void saveDone(bool successfull);
	void resetDone(bool successfull);
	void progressCanceled();

private:
	QScopedPointer<QSettingsDialogPrivate> d_ptr;
	Q_DECLARE_PRIVATE(QSettingsDialog)
};

#endif // QSETTINGSDIALOG_H
