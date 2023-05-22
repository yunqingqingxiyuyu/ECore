#ifndef CORE_GLOBAL_H
#define CORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtUiPlugin/QDesignerExportWidget>
#include <qnamespace.h>

#if defined(PLUGIN_LIBRARY)

#define CORE_EXPORT QDESIGNER_WIDGET_EXPORT

#else

#if defined(CORE_LIBRARY)
#  define CORE_EXPORT Q_DECL_EXPORT
#else
#  define CORE_EXPORT Q_DECL_IMPORT
#endif

#endif

#define Q_DECLARE_D(Class) \
    class Class##Private *d_ptr = nullptr;

namespace Ex {

    enum ItemDataRole{
        Label = Qt::UserRole + 1, //标签文本
        IndentLevel ,             //缩进层级
        Property,				  //item的属性值
    };
}

#endif // CORE_GLOBAL_H
