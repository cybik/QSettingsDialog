#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QDialog>
#include <QIcon>
class QSettingsCategory;
class QSettingsSection;
class QSettingsGroup;

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(QSettingsDialog)

	Q_PROPERTY(QSize categoryIconSize READ categoryIconSize WRITE setCategoryIconSize RESET resetCategoryIconSize)

public:
	QSettingsDialog(QWidget *parent = Q_NULLPTR);
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
	void setCategoryIconSize(QSize categoryIconSize);
	void resetCategoryIconSize();

protected:
	void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private:
	QSettingsDialogPrivate *d_ptr;
	Q_DECLARE_PRIVATE(QSettingsDialog)
};

#endif // QSETTINGSDIALOG_H
