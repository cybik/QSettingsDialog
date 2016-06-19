#include <QApplication>
#include <QDebug>
#include <qsettingsdialog.h>
#include "metawrapper.h"
#include "qsettingswidgetfactory.h"

class StateLoader : public QSimpleSettingsLoader
{
public:
	StateLoader(QVariant value = QVariant()) :
		value(value)
	{}

	bool load(QVariant &data, bool &userEdited) override {
		data = this->value;
		userEdited = true;
		return true;
	}
	bool save(const QVariant &data) override {
		qDebug() << data;
		this->value = data;
		return true;
	}
	bool reset() override {
		return true;
	}

private:
	QVariant value;
};

#define ENTRY(metatype) new QSettingsEntry(metatype, new StateLoader(), QMetaType::typeName(metatype), false, #metatype)
#define ENTRY_VALUE(metatype, value) new QSettingsEntry(metatype, new StateLoader(value), QMetaType::typeName(metatype), false, #metatype)
#define ENTRY_PARAM(metatype, ...) new QSettingsEntry(metatype, new StateLoader(), QMetaType::typeName(metatype), false, #metatype, __VA_ARGS__)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	REGISTER_FLAG_CONVERTERS(MetaWrapper::TestFlags);

	QSettingsDialog dialog;

	QObject::connect(&dialog, &QSettingsDialog::saved, [](bool close) {
		qDebug() << "---- Save completed" << (close ? "with" : "without") << "closing ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::resetted, []() {
		qDebug() << "---- Reset completed ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::canceled, []() {
		qDebug() << "---- Dialog was canceled ----";
	});

	dialog.setSection("standardMetaTypes");
	dialog.appendEntry(ENTRY(QMetaType::Bool));
	dialog.appendEntry(ENTRY(QMetaType::Int));
	dialog.appendEntry(ENTRY(QMetaType::UInt));
	dialog.appendEntry(ENTRY(QMetaType::Double));
	dialog.appendEntry(ENTRY(QMetaType::QString));
	dialog.appendEntry(ENTRY_PARAM(QMetaType::QByteArray, "placeholderText", QStringLiteral("This is a dynamic property")));
	dialog.appendEntry(ENTRY(QMetaType::Long));
	dialog.appendEntry(ENTRY(QMetaType::LongLong));
	dialog.appendEntry(ENTRY(QMetaType::Short));
	dialog.appendEntry(ENTRY(QMetaType::Char));
	dialog.appendEntry(ENTRY(QMetaType::ULong));
	dialog.appendEntry(ENTRY(QMetaType::ULongLong));
	dialog.appendEntry(ENTRY(QMetaType::UShort));
	dialog.appendEntry(ENTRY(QMetaType::SChar));
	dialog.appendEntry(ENTRY(QMetaType::UChar));
	dialog.appendEntry(ENTRY(QMetaType::Float));
	dialog.appendEntry(ENTRY(QMetaType::QDate));
	dialog.appendEntry(ENTRY(QMetaType::QTime));
	dialog.appendEntry(ENTRY(QMetaType::QColor));
	dialog.appendEntry(ENTRY(QMetaType::QStringList));
	dialog.appendEntry(ENTRY(QMetaType::QUrl));
	dialog.appendEntry(ENTRY(QMetaType::QDateTime));
	dialog.appendEntry(ENTRY(QMetaType::QFont));
	dialog.appendEntry(ENTRY(QMetaType::QKeySequence));
	dialog.appendEntry(ENTRY(QMetaType::QUuid));

	dialog.setSection("enumTypes");
	dialog.appendEntry(ENTRY_VALUE(qMetaTypeId<MetaWrapper::TestEnum>(), MetaWrapper::Value3));
	dialog.appendEntry(ENTRY_VALUE(qMetaTypeId<MetaWrapper::TestEnum>(), QVariant::fromValue(MetaWrapper::Value2)));
	dialog.appendEntry(ENTRY_VALUE(qMetaTypeId<MetaWrapper::TestFlags>(), MetaWrapper::Flag3));
	dialog.appendEntry(ENTRY_VALUE(qMetaTypeId<MetaWrapper::TestFlags>(), QVariant::fromValue<MetaWrapper::TestFlags>(MetaWrapper::Flag8)));

	dialog.openSettings();
	return a.exec();
}
