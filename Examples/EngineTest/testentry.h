#ifndef TESTENTRY_H
#define TESTENTRY_H

#include <qsettingsloaderentry.h>

class TestEntry : public QSettingsLoaderEntry
{
public:
	TestEntry(bool optional, bool working, QVariant data = QVariant(), bool hasName = true);

	QVariant load(bool &userEdited) override;
	bool save(const QVariant &data) override;
	bool reset() override;

	QString entryName() const override;
	bool isOptional() const override;
	QString tooltip() const override;
	QSettingsWidgetBase *createWidget(QWidget *parent) override;

private:
	bool optional;
	bool working;
	QVariant data;
	bool hasName;
};

#endif // TESTENTRY_H
