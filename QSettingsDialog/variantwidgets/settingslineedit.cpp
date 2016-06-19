#include "settingslineedit.h"
#include <QUrl>

SettingsLineEdit::SettingsLineEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

bool SettingsLineEdit::hasValueChanged() const
{
	return this->isModified();
}

void SettingsLineEdit::resetValueChanged()
{
	this->setModified(false);
}

void SettingsLineEdit::setValue(const QVariant &value)
{
	this->setText(value.toString());
}

QVariant SettingsLineEdit::getValue() const
{
	return this->text();
}

void SettingsLineEdit::resetValue()
{
	this->clear();
}



SettingsByteLineEdit::SettingsByteLineEdit(QWidget *parent) :
	SettingsLineEdit(parent)
{}

void SettingsByteLineEdit::setValue(const QVariant &value)
{
	this->setText(QString::fromUtf8(value.toByteArray()));
}

QVariant SettingsByteLineEdit::getValue() const
{
	return this->text().toUtf8();
}



SettingsUrlLineEdit::SettingsUrlLineEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setValidator(new QUrlValidator(this));
	connect(this, &SettingsUrlLineEdit::editingFinished, this, [this](){
		QString text = this->text();
		this->validator()->fixup(text);
		this->setText(text);
	});
}

bool SettingsUrlLineEdit::hasValueChanged() const
{
	return this->isModified();
}

void SettingsUrlLineEdit::resetValueChanged()
{
	this->setModified(false);
}

void SettingsUrlLineEdit::setValue(const QVariant &value)
{
	this->setText(value.toUrl().toString());
}

QVariant SettingsUrlLineEdit::getValue() const
{
	return QUrl(this->text());
}

void SettingsUrlLineEdit::resetValue()
{
	this->clear();
}



QUrlValidator::QUrlValidator(QObject *parent) :
	QValidator(parent)
{}

QValidator::State QUrlValidator::validate(QString &text, int &) const
{
	return QUrl::fromUserInput(text).isValid() ? Acceptable : Intermediate;
}

void QUrlValidator::fixup(QString &text) const
{
	text = QUrl::fromUserInput(text).toString();
}
