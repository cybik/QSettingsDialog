#ifndef SETTINGSLISTEDIT_H
#define SETTINGSLISTEDIT_H

#include "qsettingswidget.h"
#include <QWidget>
#include <QStringListModel>

namespace Ui {
	class SettingsListEdit;
}

class ListEditWidget : public QWidget//TODO move out of here -> new, global repo?
{
	Q_OBJECT

	Q_PROPERTY(bool buttonsVisible READ areButtonsVisible WRITE setButtonsVisible)
	Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList RESET clear NOTIFY stringListChanged)

public:
	explicit ListEditWidget(const QStringList &stringList, QWidget *parent = Q_NULLPTR);
	explicit ListEditWidget(QWidget *parent = Q_NULLPTR);
	~ListEditWidget();

	bool areButtonsVisible() const;
	QStringList stringList() const;

public slots:
	void setButtonsVisible(bool buttonsVisible);
	void setStringList(QStringList stringList);
	void clear();

signals:
	void stringListChanged(QStringList stringList);

private slots:
	void modelChanged();

	void on_actionAdd_triggered();
	void on_actionRemove_triggered();
	void on_actionMove_Up_triggered();
	void on_actionMove_Down_triggered();

private:
	Ui::SettingsListEdit *ui;
	QStringListModel *model;
};

class SettingsListEditWidget : public QSettingsWidget<ListEditWidget>
{
public:
	SettingsListEditWidget(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSLISTEDIT_H
