#ifndef QSETTINGSCONTAINERLAYOUT_P_H
#define QSETTINGSCONTAINERLAYOUT_P_H

#include "qsettingsdialog_global.h"
#include "qsettingscontainerlayout.h"
#include "containerelements.h"

class QSettingsContainerLayoutPrivate
{
public:
	inline QSettingsContainerLayoutPrivate(const QString &id, QSettingsContainerLayout::LayoutType layoutType) :
		parentElement(),
		id(id),
		layoutType(layoutType)
	{}

	inline virtual ~QSettingsContainerLayoutPrivate() {}

	QSharedPointer<QSettingsContainerLayoutPrivate> parentElement;
	const QSettingsContainerLayout::LayoutType layoutType;
	const QString id;

	virtual bool testNull() const = 0;
	QString createIdPath() const;

	virtual QString &createNameRef() = 0;
	virtual QIcon &createIconRef() = 0;
	virtual QString &createTooltipRef() = 0;
	virtual bool &createOptionalRef() = 0;

	virtual QSettingsContainerLayout creatDefaultElement(bool createNew) = 0;
	virtual QSettingsContainerLayout createEmptySubElement(const QString &id) = 0;

	virtual int elementCount() const = 0;
	virtual QSettingsContainerLayout elementAt(int index) const = 0;
	virtual int indexOfElement(const QSettingsContainerLayout &element) const = 0;
	virtual void insertElement(int index, const QSettingsContainerLayout &element) = 0;
	virtual void removeElement(int index) = 0;
	virtual void moveElement(int indexFrom, int indexTo) = 0;

};

class SettingsGroupLayout : public QSettingsContainerLayoutPrivate
{
	friend class SettingsSectionLayout;
public:
	SettingsGroupLayout(const QString &id, QSharedPointer<SettingsGroup> element) :
		QSettingsContainerLayoutPrivate(id, QSettingsContainerLayout::GroupLayout),
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

	QSettingsContainerLayout creatDefaultElement(bool) override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsContainerLayout createEmptySubElement(const QString &) override {
		throw LayoutPropertyNotDefinedException();
	}

	int elementCount() const override {
		throw LayoutPropertyNotDefinedException();
	}

	QSettingsContainerLayout elementAt(int) const override {
		throw LayoutPropertyNotDefinedException();
	}

	int indexOfElement(const QSettingsContainerLayout &) const override {
		throw LayoutPropertyNotDefinedException();
	}

	void insertElement(int, const QSettingsContainerLayout &) override {
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

class SettingsSectionLayout : public QSettingsContainerLayoutPrivate
{
	friend class SettingsCategoryLayout;
public:
	SettingsSectionLayout(const QString &id, QSharedPointer<SettingsSection> element) :
		QSettingsContainerLayoutPrivate(id, QSettingsContainerLayout::SectionLayout),
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

	QSettingsContainerLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultGroup.isNull() && createNew)
			this->element->defaultGroup = SettingsGroup::createDefaultGroup();
		return QSettingsContainerLayout(new SettingsGroupLayout(".", this->element->defaultGroup));
	}

	QSettingsContainerLayout createEmptySubElement(const QString &id) override {
		return QSettingsContainerLayout(new SettingsGroupLayout(id, QSharedPointer<SettingsGroup>(new SettingsGroup(QString()))));
	}

	int elementCount() const override {
		return this->element->groups.size();
	}

	QSettingsContainerLayout elementAt(int index) const override {
		auto entry = this->element->groups.entry(index);
		if(entry.first.type() == QMetaType::QString)
			return QSettingsContainerLayout(new SettingsGroupLayout(entry.first.toString(), entry.second.first));
		else
			return QSettingsContainerLayout(new SettingsGroupLayout(QLatin1Char('#') + entry.first.toString(), QSharedPointer<SettingsGroup>(nullptr)));
	}

	int indexOfElement(const QSettingsContainerLayout &element) const override {
		return this->element->groups.index(resolveId(element.id()));
	}

	void insertElement(int index, const QSettingsContainerLayout &element) override {
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

class SettingsCategoryLayout : public QSettingsContainerLayoutPrivate
{
	friend class SettingsRootLayout;
public:
	SettingsCategoryLayout(const QString &id, QSharedPointer<SettingsCategory> element) :
		QSettingsContainerLayoutPrivate(id, QSettingsContainerLayout::CategoryLayout),
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

	QSettingsContainerLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultSection.isNull() && createNew)
			this->element->defaultSection = SettingsSection::createDefaultSection();
		return QSettingsContainerLayout(new SettingsSectionLayout(".", this->element->defaultSection));
	}

	QSettingsContainerLayout createEmptySubElement(const QString &id) override {
		return QSettingsContainerLayout(new SettingsSectionLayout(id, QSharedPointer<SettingsSection>(new SettingsSection(QString()))));
	}

	int elementCount() const override {
		return this->element->sections.size();
	}

	QSettingsContainerLayout elementAt(int index) const override {
		auto entry = this->element->sections.entry(index);
		return QSettingsContainerLayout(new SettingsSectionLayout(entry.first, entry.second));
	}

	int indexOfElement(const QSettingsContainerLayout &element) const override {
		return this->element->sections.index(element.id());
	}

	void insertElement(int index, const QSettingsContainerLayout &element) override {
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

class SettingsRootLayout : public QSettingsContainerLayoutPrivate
{
public:
	SettingsRootLayout(const QString &id, QSharedPointer<SettingsRoot> element) :
		QSettingsContainerLayoutPrivate(id, QSettingsContainerLayout::DialogLayout),
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

	QSettingsContainerLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultCategory.isNull() && createNew)
			this->element->defaultCategory = SettingsCategory::createDefaultCategory();
		return QSettingsContainerLayout(new SettingsCategoryLayout(".", this->element->defaultCategory));
	}

	QSettingsContainerLayout createEmptySubElement(const QString &id) override {
		return QSettingsContainerLayout(new SettingsCategoryLayout(id, QSharedPointer<SettingsCategory>(new SettingsCategory(QString()))));
	}

	int elementCount() const override {
		return this->element->categories.size();
	}

	QSettingsContainerLayout elementAt(int index) const override {
		auto entry = this->element->categories.entry(index);
		return QSettingsContainerLayout(new SettingsCategoryLayout(entry.first, entry.second));
	}

	int indexOfElement(const QSettingsContainerLayout &element) const override {
		return this->element->categories.index(element.id());
	}

	void insertElement(int index, const QSettingsContainerLayout &element) override {
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
