#ifndef EWIDGETITEMPRIVATE_H
#define EWIDGETITEMPRIVATE_H

#include <QAbstractItemModel>
#include <QObject>

#include "etreewidget.h"
#include <ewidgetitem.h>
#include "core_global.h"

class EWidgetItemPrivate
{
    EWidgetItem *const q_ptr;
    Q_DECLARE_PUBLIC(EWidgetItem);
public:

    EWidgetItemPrivate(EWidgetItem *item):
        q_ptr(item),
        disabled(false),
        selected(false),
        hidden(false),
        rowGuess(-1)
    {

    }

    friend class EWidgetItem;

private:

    QVariantList display;
    uint disabled : 1;
    uint selected : 1;
    uint hidden : 1;
    int rowGuess;

    QVector<EWidgetItem*> m_childItems;
    //存显示数据
    QVector<QVariant> m_itemData;
    //存属性
    QVector<QHash<QString ,QVariant>> m_propertyToValue;
    //存除了显示Qt::DisplayRole之外的其他角色数据
    QVector<QHash<int ,QVariant>> m_itemRoleData;
    //存状态数据
    QVector<QHash<QString,QVariant>> m_itemStatData;
    //
    QVector<QBrush> m_background;
    QVector<QBrush> m_foreground;

    EWidgetItem *m_parentItem = nullptr;
};

#endif // EWIDGETITEMPRIVATE_H
