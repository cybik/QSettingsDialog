#include "commandsettingsentry.h"
#include <QLineEdit>

class QSettingsLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	QSettingsLineEdit(QWidget *parent) :
		QSettingsWidget(parent)
	{}
	void setValue(const QVariant &value) Q_DECL_OVERRIDE {
		this->setText(value.toString());
	}
	QVariant getValue() Q_DECL_OVERRIDE {
		return this->text();
	}
	void resetValue() Q_DECL_OVERRIDE {
		this->clear();
	}
};

CommandSettingsEntry::CommandSettingsEntry(QString name, bool optional) :
	name(name),
	optional(optional)
{}

QString CommandSettingsEntry::entryName() const
{
	return name;
}

bool CommandSettingsEntry::isOptional() const
{
	return optional;
}

QSettingsWidgetBase *CommandSettingsEntry::createWidget(QWidget *parent)
{
	return new QSettingsLineEdit(parent);
}

QSettingsLoader *CommandSettingsEntry::getLoader()
{
	return Q_NULLPTR;
}
