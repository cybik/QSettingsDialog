#ifndef CHECKINGHELPER_H
#define CHECKINGHELPER_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>

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
	inline void check()  {
		this->initState = true;
		this->doCheck();
	}
	inline bool checkedChanged() const {
		return this->initState != this->testChecked();
	}
	virtual bool testChecked() const = 0;
	virtual void disable() = 0;

protected:
	virtual void doCheck() = 0;

private:
	bool initState;
};

class CheckingLabel : public QLabel, public CheckingHelper
{
public:
	inline CheckingLabel(QWidget *parent = nullptr, CheckingHelper *checker = nullptr) :
		QLabel(parent),
		CheckingHelper(),
		checker(checker)
	{}

	inline bool testChecked() const override {
		if(this->checker)
			return this->checker->testChecked();
		else
			return true;
	}

	inline void disable() override {
		this->setEnabled(false);
	}

protected:
	inline void doCheck() override {
		if(this->checker)
			this->checker->check();
	}

private:
	CheckingHelper *checker;
};

class CheckingCheckBox : public QCheckBox, public CheckingHelper
{
public:
	inline CheckingCheckBox(QWidget *parent = nullptr, CheckingHelper *checker = nullptr) :
		QCheckBox(parent),
		CheckingHelper(),
		checker(checker)
	{}

	inline bool testChecked() const override {
		if(this->checker && !this->checker->testChecked())
			return false;
		else
			return this->isChecked();
	}

	inline void disable() override {
		this->setEnabled(false);
	}

protected:
	inline void doCheck() override {
		this->setChecked(true);
		if(this->checker)
			this->checker->check();
	}

private:
	CheckingHelper *checker;
};

class CheckingGroupBox : public QGroupBox, public CheckingHelper
{
public:
	inline CheckingGroupBox(QWidget *parent = nullptr) :
		QGroupBox(parent),
		CheckingHelper()
	{}

	inline bool testChecked() const override {
		if(this->isCheckable())
			return this->isChecked();
		else
			return true;
	}

	inline void disable() override {
		this->setEnabled(false);
	}

protected:
	inline void doCheck() override {
		if(this->isCheckable())
			this->setChecked(true);
	}
};

class CheckingWrapper : public CheckingHelper
{
public:
	inline CheckingWrapper(QWidget *element) :
		CheckingHelper(),
		element(element)
	{
		QObject::connect(element, &QWidget::destroyed, [this](){
			delete this;
		});
	}

	inline bool testChecked() const override {
		return true;
	}

	inline void disable() override {
		this->element->setEnabled(false);
	}

protected:
	inline void doCheck() override {}

private:
	QWidget *element;
};

#endif // CHECKINGHELPER_H
