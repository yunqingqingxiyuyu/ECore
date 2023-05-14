#include "ewidgetitem.h"

#include "ewidgetitem_p.h"

EWidgetItem::EWidgetItem(EWidgetItem *parent) :
    d_ptr(new EWidgetItemPrivate(this))
{
    Q_D(EWidgetItem);
    d->m_parentItem = parent;
    insertColumns(0,1);
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

void EWidgetItem::appendChild(EWidgetItem *item)
{
    Q_D(EWidgetItem);
    if(!item)
        return ;
    item->setParent(this);
    d->m_childItems.append(item);
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

void EWidgetItem::setColumnCount(int count)
{
    Q_D(EWidgetItem);
    for(int column = d->m_itemData.size(); column < count; ++column)
        d->m_itemData.append(QVariant());

    removeColumns(count - 1,d->m_itemData.size() - count);
}

QVariant EWidgetItem::data(int column,int role) const
{
    Q_D(const EWidgetItem);

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if(column < 0 || column >= d->m_itemData.size())
            return QVariant();
        else
            return d->m_itemData[column];
    default:
        if(column < 0 || column >= d->m_itemRoleData.size())
            return QVariant();
        else
            return d->m_itemRoleData[column][role];
    }

    return QVariant();
}


EWidgetItem* EWidgetItem::parent() const
{
    Q_D(const EWidgetItem);
    return d->m_parentItem;
}

void EWidgetItem::setParent(EWidgetItem *parent)
{
    Q_D(EWidgetItem);
    d->m_parentItem = parent;
}

int EWidgetItem::row() const
{
    Q_D(const EWidgetItem);
    if(d->m_parentItem)
        return d->m_parentItem->children().indexOf(const_cast<EWidgetItem *>(this));

    return 0;
}

bool EWidgetItem::insertChildren(int row, int count)
{
    Q_D(EWidgetItem);
    if(row < 0 || row > d->m_childItems.size())
        return false;

    for(int tempRow = 0; tempRow < count; ++tempRow)
    {
        EWidgetItem *item = new EWidgetItem(this);
        item->setColumnCount(this->colmnCount());
        d->m_childItems.insert(row,item);
    }

    return true;
}


bool EWidgetItem::insertColumns(int column, int count)
{
    Q_D(EWidgetItem);

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

    for(int tempColumn = column; tempColumn < count; ++tempColumn)
        d->m_itemData.remove(column);

    for(auto *child : qAsConst(d->m_childItems))
        child->removeColumns(column,count);

    return true;

}

bool EWidgetItem::setData(int column, const QVariant &value,int role)
{
    Q_D(EWidgetItem);

   bool flag = false;
    do{
        if(role == Qt::DisplayRole || role == Qt::EditRole)
        {
            if(column < 0 || column >= d->m_itemData.size())
                break;
            d->m_itemData[column] = value;
            flag = true;
        }
        else
        {
            if(column < 0 || column >= d->m_itemRoleData.size())
                break;
            flag = true;
            d->m_itemRoleData[column][role] = value;
        }
    }while(false);

    return flag;
}
