#include "elineeditplugin.h"
#include "ELineEdit"

#include <QtPlugin>

ELineEditPlugin::ELineEditPlugin(QObject *parent) :
    QObject(parent)
{
}


void ELineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ELineEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ELineEditPlugin::createWidget(QWidget *parent)
{
    return new ELineEdit(parent);
}

QString ELineEditPlugin::name() const
{
    return QStringLiteral("ELineEdit");
}

QString ELineEditPlugin::group() const
{
    return QStringLiteral("ECore");
}

QIcon ELineEditPlugin::icon() const
{
    return QIcon();
}

QString ELineEditPlugin::toolTip() const
{
    return QString();
}

QString ELineEditPlugin::whatsThis() const
{
    return QString();
}

bool ELineEditPlugin::isContainer() const
{
    return false;
}

QString ELineEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ELineEdit\" name=\"worldTimeClock\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>30</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>";
}

QString ELineEditPlugin::includeFile() const
{
    return QStringLiteral("ELineEdit");
}
