#ifndef EGRIDITEMPRIVATE_H
#define EGRIDITEMPRIVATE_H

#include <QAbstractItemModel>
#include <QObject>

#include "egridwidget.h"
#include <egriditem.h>
#include "core_global.h"

class EGridItemPrivate
{
    EGridItem *const q_ptr;
    Q_DECLARE_PUBLIC(EGridItem);
public:

    EGridItemPrivate(EGridItem *item):
        q_ptr(item),
        disabled(false),
        selected(false),
        hidden(false),
        rowGuess(-1)
    {

    }

    friend class EGridItem;

private:

    QVariantList display;
    uint disabled : 1;
    uint selected : 1;
    uint hidden : 1;
    int rowGuess;

    QVector<EGridItem*> m_childItems;
    //存显示数据
    QVector<QVariant> m_itemData;
    //存属性
    QHash<QString ,QVariant> m_propertyToValue;
    //存除了显示Qt::DisplayRole之外的其他角色数据
    QVector<QHash<int ,QVariant>> m_itemRoleData;
    //存状态数据
    QVector<QHash<QString,QVariant>> m_itemStatData;
    //
    QVector<QBrush> m_background;
    QVector<QBrush> m_foreground;

    EGridItem *m_parentItem = nullptr;
    EGridWidget *m_view = nullptr;
};

#endif // EWIDGETITEMPRIVATE_H
