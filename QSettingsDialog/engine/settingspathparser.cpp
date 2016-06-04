#include "settingspathparser.h"

const QRegularExpression SettingsPathParser::realIdRegex(QStringLiteral(R"__(^([0-9a-z_\-]+)$)__"),
														 QRegularExpression::CaseInsensitiveOption |
														 QRegularExpression::OptimizeOnFirstUsageOption);
const QRegularExpression SettingsPathParser::allIdRegex(QStringLiteral(R"__(^([0-9a-z_\-]*|\.)$)__"),
														QRegularExpression::CaseInsensitiveOption |
														QRegularExpression::OptimizeOnFirstUsageOption);
const QRegularExpression SettingsPathParser::fullPathRegex(QStringLiteral(R"__(^(\.\.|([0-9a-z_\-]*|\.)\/([0-9a-z_\-]*|\.)\/([0-9a-z_\-]*|\.))?$)__"),
														   QRegularExpression::CaseInsensitiveOption |
														   QRegularExpression::OptimizeOnFirstUsageOption);

void SettingsPathParser::validateId(const QString &id, bool realIdOnly)
{
	if(realIdOnly) {
		if(!realIdRegex.match(id).hasMatch())
			throw InvalidContainerPathException();
	} else {
		if(!allIdRegex.match(id).hasMatch())
			throw InvalidContainerPathException();
	}
}

QVector<QString> SettingsPathParser::parseFullPath(const QString &path)
{
	auto match = fullPathRegex.match(path);
	if(!match.hasMatch())
		throw InvalidContainerPathException();

	if(match.captured(1).isEmpty())
		return QVector<QString>(3, QString());
	else if(match.captured(1) == QStringLiteral(".."))
		return {QStringLiteral("."), QStringLiteral("."), QStringLiteral(".")};
	else {
		return {
			match.captured(2),
			match.captured(3),
			match.captured(4)
		};
	}
}

QString SettingsPathParser::createPath(const QString &categoryId, const QString &sectionId, const QString &groupId)
{
	validateId(categoryId, false);
	validateId(sectionId, false);
	validateId(groupId, false);
	return QStringList({categoryId, sectionId, groupId}).join(QLatin1Char('/'));
}
