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

class PseudoLoader : public QSettingsLoader
{
public slots:
	void loadData() Q_DECL_OVERRIDE {
		emit loadDone("test", false);
	}
	void saveData(const QVariant &data) Q_DECL_OVERRIDE {
		emit saveDone(true);
	}
	void resetData() Q_DECL_OVERRIDE {
		emit resetDone(true);
	}
};

CommandSettingsEntry::CommandSettingsEntry(QString name, bool optional) :
	name(name),
	optional(optional),
	loader(new PseudoLoader())
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

QSettingsLoader *CommandSettingsEntry::getLoader() const
{
	return loader;
}
