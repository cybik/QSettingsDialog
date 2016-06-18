#ifndef QSETTINGSDISPLAYENGINE_H
#define QSETTINGSDISPLAYENGINE_H

#include "qsettingsdialog_global.h"
class QWindow;
struct SettingsRoot;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsDisplayInstance
{
public:
	inline virtual ~QSettingsDisplayInstance() {}

	virtual void setParentWindow(QWidget *parent) = 0;
	virtual void setParentWindow(QWindow *parent) = 0;
	virtual void createUi(const QSharedPointer<SettingsRoot> &rootElement) = 0;

public slots:
	virtual void open() = 0;
	virtual int exec() = 0;

signals:
	virtual void saved(bool closed) = 0;
	virtual void resetted() = 0;
	virtual void canceled() = 0;
};

class QSETTINGSDIALOGSHARED_EXPORT QSettingsDisplayEngine
{
public:
	inline virtual ~QSettingsDisplayEngine() {}

	virtual QSettingsDisplayInstance *createInstance() = 0;
};

#endif // QSETTINGSDISPLAYENGINE_H
