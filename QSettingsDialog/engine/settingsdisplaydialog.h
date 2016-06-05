#ifndef SETTINGSDISPLAYDIALOG_H
#define SETTINGSDISPLAYDIALOG_H

#include <QDialog>

namespace Ui {
	class SettingsDisplayDialog;
}

class SettingsDisplayDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDisplayDialog(QWidget *parent = 0);
	~SettingsDisplayDialog();

private:
	Ui::SettingsDisplayDialog *ui;
};

#endif // SETTINGSDISPLAYDIALOG_H
