#ifndef CHECKINGHELPER_H
#define CHECKINGHELPER_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>

class CheckingHelper
{
public:
	inline virtual ~CheckingHelper() {}

	virtual void doCheck() = 0;
	virtual void disable() = 0;
};

class CheckingLabel : public QLabel, public CheckingHelper
{
public:
	inline CheckingLabel(QWidget *parent = nullptr, CheckingHelper *checker = nullptr) :
		QLabel(parent),
		checker(checker)
	{}

	inline void doCheck() override {
		if(this->checker)
			this->checker->doCheck();
	}

	inline void disable() override {
		this->setEnabled(false);
	}

private:
	CheckingHelper *checker;
};

class CheckingCheckBox : public QCheckBox, public CheckingHelper
{
public:
	inline CheckingCheckBox(QWidget *parent = nullptr, CheckingHelper *checker = nullptr) :
		QCheckBox(parent),
		checker(checker)
	{}

	inline void doCheck() override {
		this->setChecked(true);
		if(this->checker)
			this->checker->doCheck();
	}

	inline void disable() override {
		this->setEnabled(false);
	}

private:
	CheckingHelper *checker;
};

class CheckingGroupBox : public QGroupBox, public CheckingHelper
{
public:
	inline CheckingGroupBox(QWidget *parent = nullptr) :
		QGroupBox(parent)
	{}

	inline void doCheck() override {
		if(this->isCheckable())
			this->setChecked(true);
	}

	inline void disable() override {
		this->setEnabled(false);
	}
};

class CheckingWrapper : public CheckingHelper
{
public:
	inline CheckingWrapper(QWidget *element) :
		element(element)
	{
		QObject::connect(element, &QWidget::destroyed, [this](){
			delete this;
		});
	}

	inline void doCheck() override {}

	inline void disable() override {
		this->element->setEnabled(false);
	}

private:
	QWidget *element;
};

#endif // CHECKINGHELPER_H
