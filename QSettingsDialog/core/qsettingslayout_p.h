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
    const QString id;
    const QSettingsLayout::LayoutType layoutType;
	QPointer<QSettingsDialog> dialog;

	virtual bool testNull() const = 0;
	virtual QString createIdPath() const;

	virtual int &createDisplayIdRef() {throw LayoutPropertyNotDefinedException();}
	virtual QString &createNameRef() {throw LayoutPropertyNotDefinedException();}
	virtual QIcon &createIconRef() {throw LayoutPropertyNotDefinedException();}
	virtual QString &createTooltipRef() {throw LayoutPropertyNotDefinedException();}
	virtual bool &createOptionalRef() {throw LayoutPropertyNotDefinedException();}

	virtual QSettingsLayout creatDefaultElement(bool createNew) { Q_UNUSED(createNew);throw LayoutPropertyNotDefinedException();}
	virtual bool removeDefaultElement() {throw LayoutPropertyNotDefinedException();}
	virtual QSettingsLayout createEmptySubElement(const QString &id) {Q_UNUSED(id);throw LayoutPropertyNotDefinedException();}

	virtual int elementCount() const {throw LayoutPropertyNotDefinedException();}
	virtual QSettingsLayout elementAt(int index) const {Q_UNUSED(index);throw LayoutPropertyNotDefinedException();}
	virtual int indexOfElement(const QString &elementName) const {Q_UNUSED(elementName);throw LayoutPropertyNotDefinedException();}
	virtual void insertElement(int index, const QSettingsLayout &element) {Q_UNUSED(index);Q_UNUSED(element);throw LayoutPropertyNotDefinedException();}
	virtual void removeElement(int index) {Q_UNUSED(index);throw LayoutPropertyNotDefinedException();}
	virtual void moveElement(int indexFrom, int indexTo) {Q_UNUSED(indexFrom);Q_UNUSED(indexTo);throw LayoutPropertyNotDefinedException();}

};

class SettingsEntryLayout : public QSettingsLayoutPrivate
{
	friend class SettingsGroupLayout;
public:
	SettingsEntryLayout(int id, QSharedPointer<QSettingsEntry> element, QSettingsDialog *dialog) :
		QSettingsLayoutPrivate(QStringLiteral("#%1").arg(id), QSettingsLayout::EntryLayout, dialog),
		element(element)
	{}

	static int convertId(const QString &id) {
		return id.mid(1).toInt();
	}
	int getId() const {
		return convertId(this->id);
	}

	bool testNull() const override {
		return this->element.isNull();
	}

	QString createIdPath() const override {
		throw LayoutPropertyNotDefinedException();
	}

	QString &createNameRef() override {
		return this->element->d_ptr->name;
	}

	QString &createTooltipRef() override {
		return this->element->d_ptr->tooltip;
	}

	bool &createOptionalRef() override {
		return this->element->d_ptr->optional;
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

	bool testNull() const override {
		return this->element.isNull();
	}

	int &createDisplayIdRef() override {
		return this->element->displayId;
	}

	QString &createNameRef() override {
		return this->element->name;
	}

	QString &createTooltipRef() override {
		return this->element->tooltip;
	}

	bool &createOptionalRef() override {
		return this->element->isOptional;
	}

	int elementCount() const override {
		return this->element->entries.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->entries.entry(index);
		return new SettingsEntryLayout(entry.first, entry.second, this->dialog);
	}

	int indexOfElement(const QString &elementName) const override {
		return this->element->entries.index(SettingsEntryLayout::convertId(elementName));
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

	bool testNull() const override {
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

	QSettingsLayout createEmptySubElement(const QString &id) override {
		return QSettingsLayout(new SettingsGroupLayout(id, QSharedPointer<SettingsGroup>(new SettingsGroup(0, QString())), this->dialog));
	}

	int elementCount() const override {
		return this->element->groups.size();
	}

	QSettingsLayout elementAt(int index) const override {
		auto entry = this->element->groups.entry(index);
        if(entry.first.type() == QVariant::String)
			return QSettingsLayout(new SettingsGroupLayout(entry.first.toString(), entry.second.first, this->dialog));
		else
			return QSettingsLayout(new SettingsEntryLayout(entry.first.toInt(), entry.second.second, this->dialog));
	}

	int indexOfElement(const QString &elementName) const override {
		return this->element->groups.index(resolveId(elementName));
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
			return SettingsEntryLayout::convertId(id);
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

	bool testNull() const override {
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

	QSettingsLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultSection.isNull() && createNew)
			this->element->defaultSection = SettingsSection::createDefaultSection();
		return QSettingsLayout(new SettingsSectionLayout(".", this->element->defaultSection, this->dialog));
	}

	bool removeDefaultElement() override {
		if(!this->element->defaultSection.isNull()) {
			this->element->defaultSection.reset();
			return true;
		} else
			return false;
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

	int indexOfElement(const QString &elementName) const override {
		return this->element->sections.index(elementName);
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

	bool testNull() const override {
		return this->element.isNull();
	}

	QSettingsLayout creatDefaultElement(bool createNew) override {
		if(this->element->defaultCategory.isNull() && createNew)
			this->element->defaultCategory = SettingsCategory::createDefaultCategory();
		return QSettingsLayout(new SettingsCategoryLayout(".", this->element->defaultCategory, this->dialog));
	}

	bool removeDefaultElement() override {
		if(!this->element->defaultCategory.isNull()) {
			this->element->defaultCategory.reset();
			return true;
		} else
			return false;
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

	int indexOfElement(const QString &elementName) const override {
		return this->element->categories.index(elementName);
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
