#ifndef SETTINGSENGINE_H
#define SETTINGSENGINE_H

#include <QObject>

class SettingsEngine : public QObject
{
	Q_OBJECT
public:
	explicit SettingsEngine(QObject *parent = 0);

signals:

public slots:
};

#endif // SETTINGSENGINE_H