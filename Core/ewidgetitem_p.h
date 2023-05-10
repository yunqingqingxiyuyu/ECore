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
    QVector<QVariant> m_itemData;
    EWidgetItem *m_parentItem = nullptr;
};

#endif // EWIDGETITEMPRIVATE_H
