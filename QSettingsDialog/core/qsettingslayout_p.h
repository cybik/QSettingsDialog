#ifndef QSETTINGSCONTAINERLAYOUT_P_H
#define QSETTINGSCONTAINERLAYOUT_P_H

#include "qsettingsdialog_global.h"
#include "qsettingslayout.h"
#include "containerelements.h"
#include "qsettingsentry_p.h"

class QSettingsLayoutPrivate
{
public:
	inline QSettingsLayoutPrivate(const QString &id, QSettingsLayout::LayoutType layoutType, QSettingsDialog *dialog) :
		parentElement(),
		id(id),
		layoutType(layoutType),
		dialog(dialog)
	{}

	inline virtual ~QSettingsLayoutPrivate() {}

	QSharedPointer<QSettingsLayoutPrivate> parentElement;
	const QSettingsLayout::LayoutType layoutType;
	const QString id;
	QPointer<QSettingsDialog> dialog;

	virtual bool testNull() const = 0;
	virtual QString createIdPath() const;

	virtual QString &createNameRef() = 0;
	virtual QIcon &createIconRef() = 0;
	virtual QString &createTooltipRef() = 0;
	virtual bool &createOptionalRef() = 0;

	virtual QSettingsLayout creatDefaultElement(bool createNew) = 0;
	virtual QSettingsLayout createEmptySubElement(const QString &id) = 0;

	virtual int elementCount() const = 0;
	virtual QSettingsLayout elementAt(int index) const = 0;
	virtual int indexOfElement(const QSettingsLayout &element) const = 0;
	virtual void insertElement(int index, const QSettingsLayout &element) = 0;
	virtual void removeElement(int index) = 0;
	virtual void moveElement(int indexFrom, int indexTo) = 0;

};

class SettingsEntryLayout : public QSettingsLayoutPrivate
{
	friend class SettingsGroupLayout;
public:
	SettingsEntryLayout(int id, QSharedPointer<QSettingsEntry> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(QStringLiteral("#%1").arg(id), QSettingsLayout::EntryLayout, dialog),
		element(element)
	{}

	int getId() const {
		return this->id.mid(1).toInt();
	}
	static int getId(QSettingsLayout element) {
		auto elementPrivate = sharedSafeCast(SettingsEntryLayout, element.d_ptr);
		return elementPrivate->getId();
	}

	bool testNull() const {
		return this->element.isNull();
	}

	QString createIdPath() const override {
		throw LayoutPropertyNotDefinedException();
	}

	QString &createNameRef() override {
		return this->element->d_ptr->name;
	}

	QIcon &createIconRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QString &createTooltipRef() override {
		return this->element->d_ptr->tooltip;
	}

	bool &createOptionalRef() override {
		return this->element->d_ptr->optional;
	}

	QSettingsLayout creatDefaultElement(bool) override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout createEmptySubElement(const QString &) override {
		throw LayoutPropertyNotDefinedException();
	}

	int elementCount() const override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout elementAt(int) const override {
		throw LayoutPropertyNotDefinedException();
	}

	int indexOfElement(const QSettingsLayout &) const override {
		throw LayoutPropertyNotDefinedException();
	}

	void insertElement(int, const QSettingsLayout &) override {
		throw LayoutPropertyNotDefinedException();
	}

	void removeElement(int) override {
		throw LayoutPropertyNotDefinedException();
	}

	void moveElement(int, int) override {
		throw LayoutPropertyNotDefinedException();
	}

private:
	QSharedPointer<QSettingsEntry> element;
};

class SettingsGroupLayout : public QSettingsLayoutPrivate
{
	friend class SettingsSectionLayout;
public:
	SettingsGroupLayout(const QString &id, QSharedPointer<SettingsGroup> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(id, QSettingsLayout::GroupLayout, dialog),
		element(element)
	{}

	bool testNull() const {
		return this->element.isNull();
	}

	QString &createNameRef() override {
		return this->element->name;
	}

	QIcon &createIconRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QString &createTooltipRef() override {
		return this->element->tooltip;
	}

	bool &createOptionalRef() override {
		return this->element->isOptional;
	}

	QSettingsLayout creatDefaultElement(bool) override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout createEmptySubElement(const QString &) override {
		throw LayoutPropertyNotDefinedException();
	}

	int elementCount() const override {
		return this->element->entries.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->entries.entry(index);
		return new SettingsEntryLayout(entry.first, entry.second, this->dialog);
	}

	int indexOfElement(const QSettingsLayout &element) const override {
		return this->element->entries.index(SettingsEntryLayout::getId(element));
	}

	void insertElement(int index, const QSettingsLayout &element) override {
		auto elementPrivate = sharedSafeCast(SettingsEntryLayout, element.d_ptr);
		this->element->entries.insert(index, elementPrivate->getId(), elementPrivate->element);
	}

	void removeElement(int index) override {
		this->element->entries.remove(index);
	}

	void moveElement(int indexFrom, int indexTo) override {
		this->element->entries.move(indexFrom, indexTo);
	}

private:
	QSharedPointer<SettingsGroup> element;
};

class SettingsSectionLayout : public QSettingsLayoutPrivate
{
	friend class SettingsCategoryLayout;
public:
	SettingsSectionLayout(const QString &id, QSharedPointer<SettingsSection> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(id, QSettingsLayout::SectionLayout, dialog),
		element(element)
	{}

	bool testNull() const {
		return this->element.isNull();
	}

	QString &createNameRef() override {
		return this->element->name;
	}

	QIcon &createIconRef() override {
		return this->element->icon;
	}

	QString &createTooltipRef() override {
		return this->element->tooltip;
	}

	bool &createOptionalRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout creatDefaultElement(bool) override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsGroupLayout(id, QSharedPointer<SettingsGroup>(new SettingsGroup(QString())), this->dialog));
	}

	int elementCount() const override {
		return this->element->groups.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->groups.entry(index);
		if(entry.first.type() == QMetaType::QString)
			return QSettingsLayout(new SettingsGroupLayout(entry.first.toString(), entry.second.first, this->dialog));
		else
			return QSettingsLayout(new SettingsEntryLayout(entry.first.toInt(), entry.second.second, this->dialog));
	}

	int indexOfElement(const QSettingsLayout &element) const override {
		return this->element->groups.index(resolveId(element.id()));
	}

	void insertElement(int index, const QSettingsLayout &element) override {
		auto elementPrivate = sharedSafeCast(SettingsGroupLayout, element.d_ptr);
		this->element->groups.insert(index, elementPrivate->id, elementPrivate->element);
	}

	void removeElement(int index) override 	{
		this->element->groups.remove(index);
	}

	void moveElement(int indexFrom, int indexTo) override {
		this->element->groups.move(indexFrom, indexTo);
	}

private:
	QSharedPointer<SettingsSection> element;

	static QVariant resolveId(const QString &id) {
		if(id.startsWith(QLatin1Char('#')))
			return id.mid(1).toInt();
		else
			return id;
	}
};

class SettingsCategoryLayout : public QSettingsLayoutPrivate
{
	friend class SettingsRootLayout;
public:
	SettingsCategoryLayout(const QString &id, QSharedPointer<SettingsCategory> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(id, QSettingsLayout::CategoryLayout, dialog),
		element(element)
	{}

	bool testNull() const {
		return this->element.isNull();
	}

	QString &createNameRef() override {
		return this->element->name;
	}

	QIcon &createIconRef() override {
		return this->element->icon;
	}

	QString &createTooltipRef() override {
		return this->element->tooltip;
	}

	bool &createOptionalRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultSection.isNull() && createNew)
			this->element->defaultSection = SettingsSection::createDefaultSection();
		return QSettingsLayout(new SettingsSectionLayout(".", this->element->defaultSection, this->dialog));
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsSectionLayout(id, QSharedPointer<SettingsSection>(new SettingsSection(QString())), this->dialog));
	}

	int elementCount() const override {
		return this->element->sections.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->sections.entry(index);
		return QSettingsLayout(new SettingsSectionLayout(entry.first, entry.second, this->dialog));
	}

	int indexOfElement(const QSettingsLayout &element) const override {
		return this->element->sections.index(element.id());
	}

	void insertElement(int index, const QSettingsLayout &element) override {
		auto elementPrivate = sharedSafeCast(SettingsSectionLayout, element.d_ptr);
		this->element->sections.insert(index, elementPrivate->id, elementPrivate->element);
	}

	void removeElement(int index) override 	{
		this->element->sections.remove(index);
	}

	void moveElement(int indexFrom, int indexTo) override {
		this->element->sections.move(indexFrom, indexTo);
	}

private:
	QSharedPointer<SettingsCategory> element;
};

class SettingsRootLayout : public QSettingsLayoutPrivate
{
public:
	SettingsRootLayout(const QString &id, QSharedPointer<SettingsRoot> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(id, QSettingsLayout::DialogLayout, dialog),
		element(element)
	{}

	bool testNull() const {
		return this->element.isNull();
	}

	QString &createNameRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QIcon &createIconRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QString &createTooltipRef() override 	{
		throw LayoutPropertyNotDefinedException();
	}

	bool &createOptionalRef() override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultCategory.isNull() && createNew)
			this->element->defaultCategory = SettingsCategory::createDefaultCategory();
		return QSettingsLayout(new SettingsCategoryLayout(".", this->element->defaultCategory, this->dialog));
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsCategoryLayout(id, QSharedPointer<SettingsCategory>(new SettingsCategory(QString())), this->dialog));
	}

	int elementCount() const override {
		return this->element->categories.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->categories.entry(index);
		return QSettingsLayout(new SettingsCategoryLayout(entry.first, entry.second, this->dialog));
	}

	int indexOfElement(const QSettingsLayout &element) const override {
		return this->element->categories.index(element.id());
	}

	void insertElement(int index, const QSettingsLayout &element) override {
		auto elementPrivate = sharedSafeCast(SettingsCategoryLayout, element.d_ptr);
		this->element->categories.insert(index, elementPrivate->id, elementPrivate->element);
	}

	void removeElement(int index) override 	{
		this->element->categories.remove(index);
	}

	void moveElement(int indexFrom, int indexTo) override {
		this->element->categories.move(indexFrom, indexTo);
	}

private:
	QSharedPointer<SettingsRoot> element;
};

#endif // QSETTINGSCONTAINERLAYOUT_P_H
