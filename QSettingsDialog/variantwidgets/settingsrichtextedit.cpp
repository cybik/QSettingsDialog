#include "settingsrichtextedit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <dialogmaster.h>

SettingsRichTextEdit::SettingsRichTextEdit(QWidget *parent) :
	QSettingsWidget(parent),
	boldAction(new QAction(tr("Bold"), this)),
	italicAction(new QAction(tr("Italic"), this)),
	underlinedAction(new QAction(tr("Underlined"), this))
{
	connect(this, &SettingsRichTextEdit::cursorPositionChanged,
			this, &SettingsRichTextEdit::updateActionsStatus);

	this->boldAction->setShortcut(QKeySequence::Bold);
	this->boldAction->setCheckable(true);
	connect(this->boldAction, &QAction::triggered,
			this, [=](bool checked){
		this->setFontWeight(checked ? QFont::Bold : QFont::Normal);
	});
	this->addAction(this->boldAction);

	this->italicAction->setShortcut(QKeySequence::Italic);
	this->italicAction->setCheckable(true);
	connect(this->italicAction, &QAction::triggered,
			this, &SettingsRichTextEdit::setFontItalic);
	this->addAction(this->italicAction);

	this->underlinedAction->setShortcut(QKeySequence::Underline);
	this->underlinedAction->setCheckable(true);
	connect(this->underlinedAction, &QAction::triggered,
			this, &SettingsRichTextEdit::setFontUnderline);
	this->addAction(this->underlinedAction);

	auto seperator1 = new QAction(this);
	seperator1->setSeparator(true);
	this->addAction(seperator1);

	auto fontAction = new QAction(tr("Edit Font"), this);
	connect(fontAction, &QAction::triggered,
			this, &SettingsRichTextEdit::editFont);
	this->addAction(fontAction);

	auto colorAction = new QAction(tr("Edit Color"), this);
	connect(colorAction, &QAction::triggered,
			this, &SettingsRichTextEdit::editColor);
	this->addAction(colorAction);

	auto seperator2 = new QAction(this);
	seperator2->setSeparator(true);
	this->addAction(seperator2);
}

void SettingsRichTextEdit::setValue(const QVariant &value)
{
	this->setHtml(value.toString());
}

QVariant SettingsRichTextEdit::getValue() const
{
	return this->toHtml();
}

void SettingsRichTextEdit::resetValue()
{
	this->clear();
}

void SettingsRichTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
	auto menu = this->createStandardContextMenu(e->pos());
	menu->insertActions(menu->actions().first(), this->actions());
	menu->exec(this->mapToGlobal(e->pos()));
	menu->deleteLater();
}

void SettingsRichTextEdit::updateActionsStatus()
{
	this->boldAction->setChecked(this->fontWeight() != QFont::Normal);
	this->italicAction->setChecked(this->fontItalic());
	this->underlinedAction->setChecked(this->fontUnderline());
}

void SettingsRichTextEdit::editFont()
{
	auto ok = false;
	auto resFont = DialogMaster::getFont(&ok,
										 this->currentFont(),
										 this,
										 tr("Edit Font"));
	if(ok)
		this->setCurrentFont(resFont);
}

void SettingsRichTextEdit::editColor()
{
	auto resColor = DialogMaster::getColor(this->textColor(),
										   this,
										   tr("Edit Color"));
	if(resColor.isValid())
		this->setTextColor(resColor);
}
