#include <QApplication>
#include <QDebug>
#include <qsettingsdialog.h>

class StateLoader : public QSimpleSettingsLoader
{
public:
	bool load(QVariant &, bool &userEdited) override {
		userEdited = true;
		return true;
	}
	bool save(const QVariant &data) override {
		qDebug() << data;
		return true;
	}
	bool reset() override {
		return true;
	}
};

#define ENTRY(metatype) new QSettingsEntry(metatype, new StateLoader(), QMetaType::typeName(metatype), false, #metatype)
#define ENTRY_PARAM(metatype, ...) new QSettingsEntry(metatype, new StateLoader(), QMetaType::typeName(metatype), false, #metatype, __VA_ARGS__)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

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

	dialog.openSettings();
	return a.exec();
}
