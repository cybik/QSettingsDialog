#ifndef COMMANDSETTINGSENTRY_H
#define COMMANDSETTINGSENTRY_H

#include "qsettingsentry.h"

class CommandSettingsEntry : public QSettingsEntry
{
public:
	CommandSettingsEntry(QString name = "Baum == 42", bool optional = true);

	// QSettingsEntry interface
	QString entryName() const Q_DECL_OVERRIDE;
	bool isOptional() const Q_DECL_OVERRIDE;
	QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
	QSettingsLoader *createLoader() Q_DECL_OVERRIDE;
	void setValue(QWidget *widget, const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue(QWidget *widget) Q_DECL_OVERRIDE;
	void resetWidget(QWidget *widget) Q_DECL_OVERRIDE;

private:
	QString name;
	bool optional;
};

#endif // COMMANDSETTINGSENTRY_H
