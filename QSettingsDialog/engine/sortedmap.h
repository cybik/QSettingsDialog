#ifndef SORTEDMAP_H
#define SORTEDMAP_H

#include <QHash>
#include <QList>
#include <QSharedPointer>

template <typename TId, typename TEntry>
class SortedMap
{
public:
	typedef QPair<TId, QSharedPointer<TEntry>> Entry;

	QSharedPointer<TEntry> append(const TId &id, TEntry *entry);
	void append(const TId &id, const QSharedPointer<TEntry> &entry);
	QSharedPointer<TEntry> prepend(const TId &id, TEntry *entry);
	void prepend(const TId &id, const QSharedPointer<TEntry> &entry);
	QSharedPointer<TEntry> insert(int index, const TId &id, TEntry *entry);
	void insert(int index, const TId &id, const QSharedPointer<TEntry> &entry);

	int index(const TId &id) const;
	TId id(int index) const;

	int size() const;
	bool hasIndex(int index) const;
	bool contains(const TId &id) const;

	QList<TId> keys() const;
	TId key(int index) const;
	Entry entry(int index) const;

	QList<QSharedPointer<TEntry>> values() const;
	QSharedPointer<TEntry> value(int index) const;
	QSharedPointer<TEntry> valueId(const TId &id) const;

	bool remove(int index);
	bool removeId(const TId &id);
	QSharedPointer<TEntry> take(int index);
	QSharedPointer<TEntry> takeId(const TId &id);
	void move(int indexFrom, int indexTo);

	class const_iterator
	{
		friend class SortedMap<TId, TEntry>;
	public:
		typename SortedMap<TId, TEntry>::Entry operator*();
		bool operator!=(const const_iterator& other) const;
		const_iterator &operator++();

	private:
		const_iterator(const SortedMap<TId, TEntry> &map, int index);

		const SortedMap<TId, TEntry> &map;
		int index;
	};

	const_iterator begin() const;
	const_iterator end() const;

private:
	QHash<TId, QSharedPointer<TEntry>> entries;
	QList<TId> entryOrder;
};

// ------------------------- IMPLEMENTATIONS --------------------------

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::append(const TId &id, TEntry *entry)
{
	QSharedPointer<TEntry> entryElement(entry);
	this->append(id, entryElement);
	return entryElement;
}

template <typename TId, typename TEntry>
void SortedMap<TId, TEntry>::append(const TId &id, const QSharedPointer<TEntry> &entry)
{
	this->entries.insert(id, entry);
	if(this->entryOrder.contains(id))
		this->entryOrder.removeOne(id);
	this->entryOrder.append(id);
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::prepend(const TId &id, TEntry *entry)
{
	QSharedPointer<TEntry> entryElement(entry);
	this->prepend(id, entryElement);
	return entryElement;
}

template <typename TId, typename TEntry>
void SortedMap<TId, TEntry>::prepend(const TId &id, const QSharedPointer<TEntry> &entry)
{
	this->entries.insert(id, entry);
	if(this->entryOrder.contains(id))
		this->entryOrder.removeOne(id);
	this->entryOrder.prepend(id);
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::insert(int index, const TId &id, TEntry *entry)
{
	QSharedPointer<TEntry> entryElement(entry);
	this->insert(index, id, entryElement);
	return entryElement;
}

template <typename TId, typename TEntry>
void SortedMap<TId, TEntry>::insert(int index, const TId &id, const QSharedPointer<TEntry> &entry)
{
	Q_ASSERT(index <= this->entryOrder.size());
	this->entries.insert(id, entry);
	if(this->entryOrder.contains(id))
		this->entryOrder.removeOne(id);
	this->entryOrder.insert(index, id);
}

template <typename TId, typename TEntry>
int SortedMap<TId, TEntry>::index(const TId &id) const
{
	return this->entryOrder.indexOf(id);
}

template <typename TId, typename TEntry>
TId SortedMap<TId, TEntry>::id(int index) const
{
	Q_ASSERT(index < this->entryOrder.size());
	return this->entryOrder[index];
}

template <typename TId, typename TEntry>
int SortedMap<TId, TEntry>::size() const
{
	return this->entryOrder.size();
}

template <typename TId, typename TEntry>
bool SortedMap<TId, TEntry>::hasIndex(int index) const
{
	return (index < this->entryOrder.size() &&
			index >= 0);
}

template <typename TId, typename TEntry>
bool SortedMap<TId, TEntry>::contains(const TId &id) const
{
	return this->entries.contains(id);
}

template <typename TId, typename TEntry>
QList<TId> SortedMap<TId, TEntry>::keys() const
{
	return this->entryOrder;
}

template <typename TId, typename TEntry>
typename TId SortedMap<TId, TEntry>::key(int index) const
{
	Q_ASSERT(index < this->entryOrder.size());
	return this->entryOrder[index];
}

template <typename TId, typename TEntry>
typename SortedMap<TId, TEntry>::Entry SortedMap<TId, TEntry>::entry(int index) const
{
	Q_ASSERT(index < this->entryOrder.size());
	auto id = this->entryOrder[index];
	return {
		id,
		this->entries.value(id)
	};
}

template <typename TId, typename TEntry>
QList<QSharedPointer<TEntry>> SortedMap<TId, TEntry>::values() const
{
	QList<QSharedPointer<TEntry>> entryList;
	foreach(TId id, this->entryOrder)
		entryList.append(this->entries.value(id));
	return entryList;
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::value(int index) const
{
	Q_ASSERT(index < this->entryOrder.size());
	return this->entries.value(this->entryOrder[index]);
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::valueId(const TId &id) const
{
	return this->entries.value(id);
}

template <typename TId, typename TEntry>
bool SortedMap<TId, TEntry>::remove(int index)
{
	Q_ASSERT(index < this->entryOrder.size());
	TId id = this->entryOrder.takeAt(index);
	return this->entries.remove(id) > 0;
}

template <typename TId, typename TEntry>
bool SortedMap<TId, TEntry>::removeId(const TId &id)
{
	this->entries.remove(id);
	return this->entryOrder.removeOne(id);
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::take(int index)
{
	Q_ASSERT(index < this->entryOrder.size());
	TId id = this->entryOrder.takeAt(index);
	return this->entries.take(id);
}

template <typename TId, typename TEntry>
QSharedPointer<TEntry> SortedMap<TId, TEntry>::takeId(const TId &id)
{
	this->entryOrder.removeOne(id);
	return this->entries.take(id);
}

template <typename TId, typename TEntry>
void SortedMap<TId, TEntry>::move(int indexFrom, int indexTo)
{
	Q_ASSERT(indexFrom < this->entryOrder.size());
	Q_ASSERT(indexTo < this->entryOrder.size());
	this->entryOrder.move(indexFrom, indexTo);
}

template <typename TId, typename TEntry>
typename SortedMap<TId, TEntry>::const_iterator SortedMap<TId, TEntry>::begin() const
{
	return const_iterator((*this), 0);
}

template <typename TId, typename TEntry>
typename SortedMap<TId, TEntry>::const_iterator SortedMap<TId, TEntry>::end() const
{
	return const_iterator((*this), this->entryOrder.size());
}



template <typename TId, typename TEntry>
SortedMap<TId, TEntry>::const_iterator::const_iterator(const SortedMap<TId, TEntry> &map, int index) :
	map(map),
	index(index)
{}

template <typename TId, typename TEntry>
typename SortedMap<TId, TEntry>::Entry SortedMap<TId, TEntry>::const_iterator::operator*()
{
	return this->map.entry(this->index);
}

template <typename TId, typename TEntry>
bool SortedMap<TId, TEntry>::const_iterator::operator!=(const typename SortedMap<TId, TEntry>::const_iterator &other) const
{
	return (this->index != other.index);
}

template <typename TId, typename TEntry>
typename SortedMap<TId, TEntry>::const_iterator &SortedMap<TId, TEntry>::const_iterator::operator++()
{
	++this->index;
	return (*this);
}

#endif // SORTEDMAP_H
