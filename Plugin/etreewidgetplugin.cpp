#include "etreewidgetplugin.h"
#include "ETreeWidget"

#include <QtPlugin>

ETreeWidgetPlugin::ETreeWidgetPlugin(QObject *parent) :
    QObject(parent)
{
}


void ETreeWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ETreeWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ETreeWidgetPlugin::createWidget(QWidget *parent)
{
    return new ETreeWidget(parent);
}

QString ETreeWidgetPlugin::name() const
{
    return QStringLiteral("ETreeWidget");
}

QString ETreeWidgetPlugin::group() const
{
    return QStringLiteral("ECore");
}

QIcon ETreeWidgetPlugin::icon() const
{
    return QIcon();
}

QString ETreeWidgetPlugin::toolTip() const
{
    return QString();
}

QString ETreeWidgetPlugin::whatsThis() const
{
    return QString();
}

bool ETreeWidgetPlugin::isContainer() const
{
    return false;
}

QString ETreeWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ETreeWidget\" name=\"worldTimeClock\">\n"
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

QString ETreeWidgetPlugin::includeFile() const
{
    return QStringLiteral("ETreeWidget");
}
