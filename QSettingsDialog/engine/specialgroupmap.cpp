#include "specialgroupmap.h"

SpecialGroupMap::SpecialGroupMap()
{

}

int SpecialGroupMap::size() const
{

}

bool SpecialGroupMap::hasIndex(int index) const
{

}

SpecialGroupMap::Entry SpecialGroupMap::entry(int index) const
{

}

QList<SpecialGroupMap::Entry> SpecialGroupMap::entries(int index) const
{

}

bool SpecialGroupMap::remove(int index)
{

}

QSharedPointer<void> SpecialGroupMap::take(int index)
{

}

void SpecialGroupMap::move(int indexFrom, int indexTo)
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::append(const QString &id, SettingsGroup *entry)
{

}

void SpecialGroupMap::append(const QString &id, const QSharedPointer<SettingsGroup> &entry)
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::prepend(const QString &id, SettingsGroup *entry)
{

}

void SpecialGroupMap::prepend(const QString &id, const QSharedPointer<SettingsGroup> &entry)
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::insert(int index, const QString &id, SettingsGroup *entry)
{

}

void SpecialGroupMap::insert(int index, const QString &id, const QSharedPointer<SettingsGroup> &entry)
{

}

int SpecialGroupMap::index(const QString &id) const
{

}

QString SpecialGroupMap::idGroup(int index) const
{

}

bool SpecialGroupMap::contains(const QString &id) const
{

}

QList<QString> SpecialGroupMap::groupKeys() const
{

}

QString SpecialGroupMap::groupKey(int index) const
{

}

QList<QSharedPointer<SettingsGroup> > SpecialGroupMap::groupValues() const
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::groupValue(int index) const
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::valueId(const QString &id) const
{

}

bool SpecialGroupMap::removeId(const QString &id)
{

}

QSharedPointer<SettingsGroup> SpecialGroupMap::takeId(const QString &id)
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::append(const int &id, QSettingsEntry *entry)
{

}

void SpecialGroupMap::append(const int &id, const QSharedPointer<QSettingsEntry> &entry)
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::prepend(const int &id, QSettingsEntry *entry)
{

}

void SpecialGroupMap::prepend(const int &id, const QSharedPointer<QSettingsEntry> &entry)
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::insert(int index, const int &id, QSettingsEntry *entry)
{

}

void SpecialGroupMap::insert(int index, const int &id, const QSharedPointer<QSettingsEntry> &entry)
{

}

int SpecialGroupMap::index(const int &id) const
{

}

int SpecialGroupMap::idCustom(int index) const
{

}

bool SpecialGroupMap::contains(const int &id) const
{

}

QList<int> SpecialGroupMap::customKeys() const
{

}

int SpecialGroupMap::customKey(int index) const
{

}

QList<QSharedPointer<QSettingsEntry> > SpecialGroupMap::customValues() const
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::customValue(int index) const
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::valueId(const int &id) const
{

}

bool SpecialGroupMap::removeId(const int &id)
{

}

QSharedPointer<QSettingsEntry> SpecialGroupMap::takeId(const int &id)
{

}

SpecialGroupMap::const_iterator SpecialGroupMap::begin() const
{

}

SpecialGroupMap::const_iterator SpecialGroupMap::end() const
{

}

SpecialGroupMap::Entry SpecialGroupMap::const_iterator::operator*()
{

}

bool SpecialGroupMap::const_iterator::operator!=(const SpecialGroupMap::const_iterator &other) const
{

}

SpecialGroupMap::const_iterator &SpecialGroupMap::const_iterator::operator++()
{

}

SpecialGroupMap::const_iterator::const_iterator(const SpecialGroupMap &map, int index)
{

}
