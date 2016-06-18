#ifndef TESTENTRY_H
#define TESTENTRY_H

#include <qsettingsloaderentry.h>

class TestEntry : public QSettingsLoaderEntry
{
public:
	TestEntry(bool optional, bool working, QVariant data = QVariant(), bool hasName = true);

	bool load(QVariant outParam data, bool outParam userEdited) override;
	bool save(const QVariant &data) override;
	bool reset() override;

private:
	QVariant data;
};

#endif // TESTENTRY_H
