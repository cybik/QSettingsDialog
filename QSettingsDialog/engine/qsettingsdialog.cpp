#include "qsettingsdialog.h"

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}



QSettingsDialog::QSettingsDialog(QObject *parent) : QObject(parent)
{

}

QString QSettingsDialog::containerPath() const
{

}

QString QSettingsDialog::categoryId() const
{

}

QString QSettingsDialog::sectionId() const
{

}

QString QSettingsDialog::groupId() const
{

}

QString QSettingsDialog::name(const QString &containerPath) const
{

}

QIcon QSettingsDialog::icon(const QString &containerPath) const
{

}

QString QSettingsDialog::tooltip(const QString &containerPath) const
{

}

bool QSettingsDialog::isOptional(const QString &groupPath) const
{

}

void QSettingsDialog::setCategory(const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{

}

void QSettingsDialog::setSection(const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{

}

void QSettingsDialog::setGroup(const QString &id, const QString &name, bool optional, const QString &tooltip)
{

}

void QSettingsDialog::setContainer(const QString &containerPath)
{

}

void QSettingsDialog::moveContainer(const QString &fromPath, const QString &toPath)
{

}

void QSettingsDialog::setName(const QString &containerPath, const QString &name)
{

}

void QSettingsDialog::setIcon(const QString &containerPath, const QIcon &icon)
{

}

void QSettingsDialog::setTooltip(const QString &containerPath, const QString &tolltip)
{

}

void QSettingsDialog::setOptional(const QString &groupPath, bool optional)
{

}

void QSettingsDialog::setOptional(bool optional)
{

}

int QSettingsDialog::addEntry(QSettingsEntry *entry)
{

}

int QSettingsDialog::addEntry(const QString &containerPath, QSettingsEntry *entry)
{

}

QSettingsEntry *QSettingsDialog::getEntry(int id) const
{
}

bool QSettingsDialog::removeEntry(int id)
{

}

void QSettingsDialog::moveEntry(int id, const QString &targetContainerPath)
{

}

QString QSettingsDialog::createContainerPath(const QString &category, const QString &section, const QString &group, bool escapeAll)
{

}

QSettingsDialog *QSettingsDialog::defaultInstance()
{

}

void QSettingsDialog::showSettings(QWidget *parentWindow)
{

}
