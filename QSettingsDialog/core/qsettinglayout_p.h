#ifndef QSETTINGSCONTAINERLAYOUT_P_H
#define QSETTINGSCONTAINERLAYOUT_P_H

#include "qsettingsdialog_global.h"
#include "qsettingslayout.h"
#include "containerelements.h"

class QSettingsLayoutPrivate
{
public:
	inline QSettingsLayoutPrivate(const QString &id, QSettingsLayout::LayoutType layoutType) :
		parentElement(),
		id(id),
		layoutType(layoutType)
	{}

	inline virtual ~QSettingsLayoutPrivate() {}

	QSharedPointer<QSettingsLayoutPrivate> parentElement;
	const QSettingsLayout::LayoutType layoutType;
	const QString id;

	virtual bool testNull() const = 0;
	QString createIdPath() const;

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

class SettingsGroupLayout : public QSettingsLayoutPrivate
{
	friend class SettingsSectionLayout;
public:
	SettingsGroupLayout(const QString &id, QSharedPointer<SettingsGroup> element) :
		QSettingsLayoutPrivate(id, QSettingsLayout::GroupLayout),
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
	QSharedPointer<SettingsGroup> element;
};

class SettingsSectionLayout : public QSettingsLayoutPrivate
{
	friend class SettingsCategoryLayout;
public:
	SettingsSectionLayout(const QString &id, QSharedPointer<SettingsSection> element) :
		QSettingsLayoutPrivate(id, QSettingsLayout::SectionLayout),
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
		if(this->element->defaultGroup.isNull() && createNew)
			this->element->defaultGroup = SettingsGroup::createDefaultGroup();
		return QSettingsLayout(new SettingsGroupLayout(".", this->element->defaultGroup));
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsGroupLayout(id, QSharedPointer<SettingsGroup>(new SettingsGroup(QString()))));
	}

	int elementCount() const override {
		return this->element->groups.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->groups.entry(index);
		if(entry.first.type() == QMetaType::QString)
			return QSettingsLayout(new SettingsGroupLayout(entry.first.toString(), entry.second.first));
		else
			return QSettingsLayout(new SettingsGroupLayout(QLatin1Char('#') + entry.first.toString(), QSharedPointer<SettingsGroup>(nullptr)));
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
	SettingsCategoryLayout(const QString &id, QSharedPointer<SettingsCategory> element) :
		QSettingsLayoutPrivate(id, QSettingsLayout::CategoryLayout),
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
		return QSettingsLayout(new SettingsSectionLayout(".", this->element->defaultSection));
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsSectionLayout(id, QSharedPointer<SettingsSection>(new SettingsSection(QString()))));
	}

	int elementCount() const override {
		return this->element->sections.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->sections.entry(index);
		return QSettingsLayout(new SettingsSectionLayout(entry.first, entry.second));
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
	SettingsRootLayout(const QString &id, QSharedPointer<SettingsRoot> element) :
		QSettingsLayoutPrivate(id, QSettingsLayout::DialogLayout),
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
		return QSettingsLayout(new SettingsCategoryLayout(".", this->element->defaultCategory));
	}

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsCategoryLayout(id, QSharedPointer<SettingsCategory>(new SettingsCategory(QString()))));
	}

	int elementCount() const override {
		return this->element->categories.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->categories.entry(index);
		return QSettingsLayout(new SettingsCategoryLayout(entry.first, entry.second));
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
