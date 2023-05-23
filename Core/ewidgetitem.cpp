#include "ewidgetitem.h"

#include "ewidgetitem_p.h"
#include <ETreeModel>
#include <QDebug>

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

void EWidgetItem::addChild(EWidgetItem *item)
{
    appendChild(item);
}


void EWidgetItem::appendChild(EWidgetItem *item)
{
    Q_D(EWidgetItem);
    if(!item)
        return ;
    item->setParent(this);
    item->setIndentLevel(this->data(0,Ex::IndentLevel).toInt() + 1);
    d->m_childItems.append(item);
}

void EWidgetItem::setIndentLevel(int level)
{
    Q_D(EWidgetItem);

    this->setData(0,level,Ex::IndentLevel);

    for(auto &&item : d->m_childItems)
        item->setIndentLevel(level + 1);
}

void EWidgetItem::setSelected(bool select)
{
//    const ETreeModel *model = tree
}

ETreeModel* EWidgetItem::model(ETreeWidget *v) const
{
    Q_D(const EWidgetItem);
    if(!v)
        v = d->m_view;

    return (v ? qobject_cast<ETreeModel *>(v->model()) : nullptr);
}

void EWidgetItem::appendChildren(const QVector<EWidgetItem *> &children)
{
    Q_D(EWidgetItem);

    for(auto && item : children)
    {
        if(!item)
            continue;
        item->setParent(this);
    }

    d->m_childItems.append(children);
}

void EWidgetItem::setBackgroudBrush(int column, const QBrush &brush)
{
    Q_D(EWidgetItem);

    if(column >= 0 || column < d->m_background.size())
        d->m_background[column] = brush;
}

QBrush EWidgetItem::backgroundBrush(int column) const
{
    Q_D(const EWidgetItem);
    if(column < 0 || column >= d->m_background.size())
        return QBrush();

    return d->m_background.at(column);
}

QBrush EWidgetItem::forebackgroundBrush(int column) const
{
    Q_D(const EWidgetItem);
    if(column < 0 || column >= d->m_foreground.size())
        return QBrush();

    return d->m_foreground.at(column);
}

void EWidgetItem::setForebackgroundBrush(int column, const QBrush &brush)
{
    Q_D(EWidgetItem);

    if(column >= 0 || column < d->m_background.size())
        d->m_foreground[column] = brush;
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

int EWidgetItem::columnCount() const
{
    Q_D(const EWidgetItem);
    return d->m_itemData.count();
}

void EWidgetItem::setColumnCount(int count)
{
    Q_D(EWidgetItem);
    for(int column = d->m_itemData.size(); column < count; ++column)
    {
        d->m_itemData.append(QVariant());
        d->m_itemRoleData.append(QHash<int ,QVariant>());
        d->m_propertyToValue.append(QHash<QString ,QVariant>());
    }

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
    case Qt::BackgroundRole:
        return backgroundBrush(column);
    case Qt::ForegroundRole:
        return forebackgroundBrush(column);
    case Ex::IndentLevel:
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
        item->setColumnCount(this->columnCount());
        d->m_childItems.insert(row,item);
    }

    return true;
}


bool EWidgetItem::insertColumns(int column, int count)
{
    Q_D(EWidgetItem);

    for(int tempColumn = 0; tempColumn < count; ++tempColumn)
    {
        d->m_itemData.insert(column,QVariant());
        d->m_itemRoleData.insert(column,QHash<int ,QVariant>());
        d->m_propertyToValue.insert(column,QHash<QString ,QVariant>());
    }

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
    {
        d->m_itemData.remove(column);
        d->m_itemRoleData.remove(column);
    }

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

void EWidgetItem::setProperty(int column,const QString &name, const QVariant &value)
{
    if(column < 0 || column >= columnCount())
        return ;

    Q_D(EWidgetItem);

    d->m_propertyToValue[column][name] = value;
}

QVariant EWidgetItem::property(int column, const QString &name)
{
    if(column < 0 || column >= columnCount())
        return name;

    Q_D(const EWidgetItem);

    return d->m_propertyToValue[column].value(name,name);
}
