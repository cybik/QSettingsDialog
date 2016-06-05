#ifndef SETTINGSPATHPARSER_H
#define SETTINGSPATHPARSER_H

#include <QString>
#include <QRegularExpression>
#include <QVector>
#include "qsettingsdialog.h"

class SettingsPathParser
{
public:
	static void validateId(const QString &id, bool realIdOnly);
	static QVector<QString> parseFullPath(const QString &path);
	static QStringList parsePartialPath(const QString &path);

	static QString createPath(const QString &categoryId, const QString &sectionId, const QString &groupId);

private:
	static const QRegularExpression realIdRegex;
	static const QRegularExpression allIdRegex;
	static const QRegularExpression fullPathRegex;
	static const QRegularExpression partialPathRegex;
};

#endif // SETTINGSPATHPARSER_H
