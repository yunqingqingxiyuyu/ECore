#include "etimewidgetplugin.h"

//#include "ETimeWidget"

#include <QtPlugin>
#include <QWidget>

ETimeWidgetPlugin::ETimeWidgetPlugin(QObject *parent) :
    QObject(parent)
{

}

void ETimeWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ETimeWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ETimeWidgetPlugin::createWidget(QWidget *parent)
{
//    return new ETimeWidget(parent);
    return new QWidget(parent);
}

QString ETimeWidgetPlugin::name() const
{
    return QStringLiteral("ETimeWidget");
}

QString ETimeWidgetPlugin::group() const
{
    return QStringLiteral("ECore");
}

QIcon ETimeWidgetPlugin::icon() const
{
    return QIcon();
}

QString ETimeWidgetPlugin::toolTip() const
{
    return QString();
}

QString ETimeWidgetPlugin::whatsThis() const
{
    return QStringLiteral("一个时间选择控件");
}

bool ETimeWidgetPlugin::isContainer() const
{
    return false;
}

QString ETimeWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ETimeWidget\" name=\"worldTimeClock\">\n"
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

QString ETimeWidgetPlugin::includeFile() const
{
    return QStringLiteral("ETimeWidget");
}
