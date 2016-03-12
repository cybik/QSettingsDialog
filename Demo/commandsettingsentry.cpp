#include "commandsettingsentry.h"
#include <QLineEdit>

class QSettingsLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	QSettingsLineEdit(QWidget *parent) :
		QSettingsWidget(parent)
	{}
	bool hasValueChanged() const Q_DECL_OVERRIDE {
		return isModified();
	}
	void resetValueChanged() Q_DECL_OVERRIDE {
		setModified(false);
	}
	void setValue(const QVariant &value) Q_DECL_OVERRIDE {
		setText(value.toString());
	}
	QVariant getValue() Q_DECL_OVERRIDE {
		return text();
	}
	void resetValue() Q_DECL_OVERRIDE {
		clear();
	}
};

CommandSettingsEntry::CommandSettingsEntry(QString name, bool optional) :
	name(name),
	optional(optional),
	value("test"),
	origVal("test"),
	mod(false)
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

void CommandSettingsEntry::loadData() {
	emit loadDone(value, mod);
}

void CommandSettingsEntry::saveData(const QVariant &data)
{
	value = data;
	mod = true;
	emit saveDone(true);
}

void CommandSettingsEntry::resetData()
{
	value = origVal;
	mod = false;
	emit resetDone(true);
}
