#include "ewidgetitem.h"

#include "ewidgetitem_p.h"

EWidgetItem::EWidgetItem(const QVector<QVariant > &data,EWidgetItem *parent):
    d_ptr(new EWidgetItemPrivate(this))
{
    Q_D(EWidgetItem);
    d->m_itemData = data;
    d->m_parentItem = parent;
}

EWidgetItem::~EWidgetItem()
{
    Q_D(EWidgetItem);
    qDeleteAll(d->m_childItems);
}

EWidgetItem* EWidgetItem::child(int number) const
{
    Q_D(const EWidgetItem);
    if(number < 0 || number >= d->m_childItems.size())
        return nullptr;

    return d->m_childItems.at(number);
}

QVector<EWidgetItem *> EWidgetItem::children() const
{
    Q_D(const EWidgetItem);

    return d->m_childItems;
}

int EWidgetItem::childCount() const
{
    Q_D(const EWidgetItem);
    return d->m_childItems.size();
}

int EWidgetItem::indexOfParent() const
{
    Q_D(const EWidgetItem);
    if(d->m_parentItem)
        return d->m_parentItem->children().indexOf(const_cast<EWidgetItem *>(this));
    return 0;
}

int EWidgetItem::colmnCount() const
{
    Q_D(const EWidgetItem);
    return d->m_itemData.count();
}

QVariant EWidgetItem::data(int column,int role) const
{
    Q_D(const EWidgetItem);
    Q_UNUSED(role);
    if(column < 0 || column >= d->m_itemData.size())
        return QVariant();

    return d->m_itemData.at(column);
}


EWidgetItem* EWidgetItem::parent() const
{
    Q_D(const EWidgetItem);
    return d->m_parentItem;
}


bool EWidgetItem::insertChildren(int row, int count, int columns)
{
    Q_D(EWidgetItem);
    if(row < 0 || row > d->m_childItems.size())
        return false;

    for(int tempRow = 0; tempRow < count; ++tempRow)
    {
        QVector<QVariant> data(columns);
        EWidgetItem *item = new EWidgetItem(data,this);
        d->m_childItems.insert(row,item);
    }

    return true;
}


bool EWidgetItem::insertColumns(int column, int count)
{
    Q_D(EWidgetItem);
    if(column < 0  || column > d->m_itemData.size())
        return false;

    for(int tempColumn = 0; tempColumn < count; ++tempColumn)
        d->m_itemData.insert(column,QVariant());

    for(auto *child : qAsConst(d->m_childItems))
        child->insertColumns(column,count);

    return true;
}


bool EWidgetItem::removeChildren(int column, int count)
{
    Q_D(EWidgetItem);
    if(column < 0 || column + count > d->m_itemData.size())
        return false;

    for(int row = 0; row < count; ++row)
        delete d->m_childItems.takeAt(column);

    return true;
}

bool EWidgetItem::removeColumns(int column, int count)
{
    Q_D(EWidgetItem);
    if(column < 0 || column + count > d->m_itemData.size())
        return false;

    for(int tempColumn = 0; tempColumn < count; ++tempColumn)
        d->m_itemData.remove(column);

    for(auto *child : qAsConst(d->m_childItems))
        child->removeColumns(column,count);

    return true;

}

bool EWidgetItem::setData(int column, const QVariant &value)
{
    Q_D(EWidgetItem);
    if(column < 0 || column >= d->m_itemData.size())
        return false;

    d->m_itemData[column] = value;

    return true;
}
