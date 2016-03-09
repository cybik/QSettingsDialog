#ifndef STANDARDSETTINGSGROUP_H
#define STANDARDSETTINGSGROUP_H

#include "qsettingsgroup.h"
#include <QString>
class QGroupBox;
class QFormLayout;

class StandardSettingsGroup : public QSettingsGroup
{
public:
	bool isActivated() const Q_DECL_OVERRIDE;
	QString name() const Q_DECL_OVERRIDE;
	bool isOptional() const Q_DECL_OVERRIDE;
	void setName(const QString &name) Q_DECL_OVERRIDE;
	void setOptional(bool optional) Q_DECL_OVERRIDE;

protected:
	QWidget *contentWidget() Q_DECL_OVERRIDE;

private:
	QGroupBox *box;
	QFormLayout *layout;

	StandardSettingsGroup(QGroupBox *box);
	StandardSettingsGroup(QWidget *widget);
	~QSettingsGroup();
};

#endif // STANDARDSETTINGSGROUP_H
