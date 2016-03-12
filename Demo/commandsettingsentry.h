#ifndef COMMANDSETTINGSENTRY_H
#define COMMANDSETTINGSENTRY_H

#include "qsettingsloaderentry.h"

class CommandSettingsEntry : public QSettingsLoaderEntry
{
public:
	CommandSettingsEntry(QString name = "Baum == 42", bool optional = true);

	// QSettingsEntry interface
	QString entryName() const Q_DECL_OVERRIDE;
	bool isOptional() const Q_DECL_OVERRIDE;
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_OVERRIDE;

public slots:
	void loadData() Q_DECL_OVERRIDE;
	void saveData(const QVariant &data) Q_DECL_OVERRIDE;
	void resetData() Q_DECL_OVERRIDE;
private:
	QString name;
	bool optional;

	QVariant value;
	QVariant origVal;
	bool mod;
};

#endif // COMMANDSETTINGSENTRY_H
