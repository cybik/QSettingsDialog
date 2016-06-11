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
};

#endif // CHECKINGHELPER_H
