#include "settingsdisplaydialog.h"
#include "ui_settingsdisplaydialog.h"

SettingsDisplayDialog::SettingsDisplayDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDisplayDialog)
{
	ui->setupUi(this);
}

SettingsDisplayDialog::~SettingsDisplayDialog()
{
	delete ui;
}
