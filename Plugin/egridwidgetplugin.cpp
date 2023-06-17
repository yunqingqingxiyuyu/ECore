#include "egridwidgetplugin.h"
#include "EGridWidget"

#include <QtPlugin>

EGridWidgetPlugin::EGridWidgetPlugin(QObject *parent) :
    QObject(parent)
{
}


void EGridWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool EGridWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *EGridWidgetPlugin::createWidget(QWidget *parent)
{
    return new EGridWidget(parent);
}

QString EGridWidgetPlugin::name() const
{
    return QStringLiteral("EGridWidget");
}

QString EGridWidgetPlugin::group() const
{
    return QStringLiteral("ECore");
}

QIcon EGridWidgetPlugin::icon() const
{
    return QIcon();
}

QString EGridWidgetPlugin::toolTip() const
{
    return QString();
}

QString EGridWidgetPlugin::whatsThis() const
{
    return QString();
}

bool EGridWidgetPlugin::isContainer() const
{
    return false;
}

QString EGridWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"EGridWidget\" name=\"worldTimeClock\">\n"
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

QString EGridWidgetPlugin::includeFile() const
{
    return QStringLiteral("EGridWidget");
}
