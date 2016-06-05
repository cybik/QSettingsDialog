#ifndef TESTENTRY_H
#define TESTENTRY_H

#include <qsettingsloaderentry.h>

class TestEntry : public QSettingsLoaderEntry
{
public:
	TestEntry();

	QVariant load(bool &userEdited) override;
	bool save(const QVariant &data) override;
	bool reset() override;

	QString entryName() const override;
	bool isOptional() const override;
	QSettingsWidgetBase *createWidget(QWidget *parent) override;
};

#endif // TESTENTRY_H
