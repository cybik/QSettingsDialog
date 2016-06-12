#ifndef SWIDGET_H
#define SWIDGET_H

#include <qsettingswidget.h>
#include <QLineEdit>

class TestWidget : public QSettingsWidget<QLineEdit>
{
public:
	TestWidget(QWidget *parent, bool ttip, QString pattern = QString()) :
		QSettingsWidget(parent),
		pattern(pattern)
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
	bool searchExpression(const QRegularExpression &regex) override {
		return regex.match(pattern).hasMatch();
	}

private:
	QString pattern;
};

#endif // SWIDGET_H
