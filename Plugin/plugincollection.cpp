#include "elineeditplugin.h"
#include "etimewidgetplugin.h"
#include "plugincollection.h"

PluginCollection::PluginCollection(QObject *parent) :
    QObject(parent)
{
    m_widgets.append(new ELineEditPlugin(this));
    m_widgets.append(new ETimeWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> PluginCollection::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(groupplugin, Group)
#endif // QT_VERSION < 0x050000
