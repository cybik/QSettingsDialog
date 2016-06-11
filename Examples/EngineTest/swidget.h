#ifndef SWIDGET_H
#define SWIDGET_H

#include <qsettingswidget.h>
#include <QLineEdit>

class TestWidget : public QSettingsWidget<QLineEdit>
{
public:
	TestWidget(QWidget *parent, bool ttip) :
		QSettingsWidget(parent)
	{
		if(ttip)
			this->setToolTip("Mikeichalt");
	}

	void setValue(const QVariant &value) override {
		this->setText(value.toString());
	}
	QVariant getValue() const override {
		return this->text();
	}
	void resetValue() override {
		this->clear();
	}
};

#endif // SWIDGET_H
