#ifndef CHECKINGHELPER_H
#define CHECKINGHELPER_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include "qsettingsgroupwidget.h"

class CheckingHelper
{
public:
	inline CheckingHelper() :
		initState(false)
	{}
	inline virtual ~CheckingHelper() {}

	inline void resetInitState() {
		this->initState = this->testChecked();
	}
	virtual void doCheck() = 0;
	inline bool checkedChanged() const {
		return this->initState != this->testChecked();
	}
	virtual bool testChecked() const = 0;
	virtual void disableLabel() = 0;

private:
	bool initState;
};

class CheckingLabel : public QLabel, public CheckingHelper
{
public:
	inline CheckingLabel(QWidget *parent = nullptr) :
		QLabel(parent),
		CheckingHelper()
	{}

	inline void doCheck() override {}

	inline bool testChecked() const override {
		return true;
	}

	inline void disableLabel() override {
		this->setEnabled(false);
	}
};

class CheckingCheckBox : public QCheckBox, public CheckingHelper
{
public:
	inline CheckingCheckBox(QWidget *parent = nullptr) :
		QCheckBox(parent),
		CheckingHelper()
	{}

	inline void doCheck() override {
		this->setChecked(true);
	}

	inline bool testChecked() const override {
		return this->isChecked();
	}

	inline void disableLabel() override {
		this->setEnabled(false);
	}
};

class GroupCheckingHelper : public CheckingHelper
{
public:
	inline GroupCheckingHelper(QSettingsGroupWidgetBase *element, QSharedPointer<QSettingsEntry> entry) :
		CheckingHelper(),
		element(element),
		entry(entry)
	{
		QObject::connect(element->asWidget(), &QWidget::destroyed, [this](){
			delete this;
		});
	}

	inline void doCheck() override {
		this->element->setEntryChecked(this->entry, true);
		this->element->setChecked(true);
	}

	inline bool testChecked() const override {
		if(this->element->isChecked())
			return this->element->isEntryChecked(this->entry);
		else
			return false;
	}

	inline void disableLabel() override {
		this->element->setEntryLabelEnabled(this->entry, false);
	}

private:
	QSettingsGroupWidgetBase *element;
	QSharedPointer<QSettingsEntry> entry;
};

#endif // CHECKINGHELPER_H
