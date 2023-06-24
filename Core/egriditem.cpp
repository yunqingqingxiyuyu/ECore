#include "egriditem.h"

#include "egriditem_p.h"
#include <EGridModel>
#include <QDebug>

EGridItem::EGridItem(EGridItem *parent, int type):
    rtti(type),
    d_ptr(new EGridItemPrivate(this)),
    itemFlags(Qt::ItemIsSelectable
              |Qt::ItemIsUserCheckable
              |Qt::ItemIsEnabled
              |Qt::ItemIsDragEnabled
              |Qt::ItemIsDropEnabled)
{
    Q_D(EGridItem);
    d->m_parentItem = parent;
}

EGridItem::EGridItem(const QStringList &strings, EGridItem *parent , int type):
    rtti(type),
    d_ptr(new EGridItemPrivate(this)),
    itemFlags(Qt::ItemIsSelectable
              |Qt::ItemIsUserCheckable
              |Qt::ItemIsEnabled
              |Qt::ItemIsDragEnabled
              |Qt::ItemIsDropEnabled)
{
    Q_D(EGridItem);
    d->m_parentItem = parent;
    for(int i = 0; i < strings.size(); ++i)
        setText(i,strings.at(i));
}

EGridItem::EGridItem(const QVector<QString> &datas, EGridItem *parent, int type):
    rtti(type),
    d_ptr(new EGridItemPrivate(this)),
    itemFlags(Qt::ItemIsSelectable
              |Qt::ItemIsUserCheckable
              |Qt::ItemIsEnabled
              |Qt::ItemIsDragEnabled
              |Qt::ItemIsDropEnabled)
{
    Q_D(EGridItem);
    d->m_parentItem = parent;
    for(int i = 0; i < datas.size(); ++i)
        setText(i,datas.at(i));
}

EGridItem::~EGridItem()
{
    Q_D(EGridItem);
    qDeleteAll(d->m_childItems);
}

void EGridItem::addChild(EGridItem *item)
{
    appendChild(item);
}


void EGridItem::appendChild(EGridItem *item)
{
    Q_D(EGridItem);
    if(!item)
        return ;
    item->setParent(this);
    item->setIndentLevel(this->data(0,Ex::IndentLevel).toInt() + 1);
    d->m_childItems.append(item);
}

void EGridItem::setIndentLevel(int level)
{
    Q_D(EGridItem);

    this->setData(0,level,Ex::IndentLevel);

    for(auto &&item : d->m_childItems)
        item->setIndentLevel(level + 1);
}

void EGridItem::setSelected(bool select)
{
    Q_UNUSED(select)
//    const EGridModel *model = tree
}

EGridModel* EGridItem::model(EGridWidget *v) const
{
    Q_D(const EGridItem);
    if(!v)
        v = d->m_view;

    return (v ? qobject_cast<EGridModel *>(v->model()) : nullptr);
}

void EGridItem::appendChildren(const QVector<EGridItem *> &children)
{
    Q_D(EGridItem);

    for(auto && item : children)
    {
        if(!item)
            continue;
        item->setParent(this);
    }

    d->m_childItems.append(children);
}

void EGridItem::setBackgroudBrush(int column, const QBrush &brush)
{
    Q_D(EGridItem);

    if(column >= 0 || column < d->m_background.size())
        d->m_background[column] = brush;
}

QBrush EGridItem::backgroundBrush(int column) const
{
    Q_D(const EGridItem);
    if(column < 0 || column >= d->m_background.size())
        return QBrush();

    return d->m_background.at(column);
}

QBrush EGridItem::forebackgroundBrush(int column) const
{
    Q_D(const EGridItem);
    if(column < 0 || column >= d->m_foreground.size())
        return QBrush();

    return d->m_foreground.at(column);
}

void EGridItem::setForebackgroundBrush(int column, const QBrush &brush)
{
    Q_D(EGridItem);

    if(column >= 0 || column < d->m_background.size())
        d->m_foreground[column] = brush;
}

EGridItem* EGridItem::child(int number) const
{
    Q_D(const EGridItem);
    if(number < 0 || number >= d->m_childItems.size())
        return nullptr;

    return d->m_childItems.at(number);
}

QVector<EGridItem *> EGridItem::children() const
{
    Q_D(const EGridItem);

    return d->m_childItems;
}

int EGridItem::childCount() const
{
    Q_D(const EGridItem);
    return d->m_childItems.size();
}

int EGridItem::indexOfParent() const
{
    Q_D(const EGridItem);
    if(d->m_parentItem)
        return d->m_parentItem->children().indexOf(const_cast<EGridItem *>(this));
    return 0;
}

int EGridItem::columnCount() const
{
    Q_D(const EGridItem);
    return d->m_itemData.count();
}

void EGridItem::setColumnCount(int count)
{
    Q_D(EGridItem);
    for(int column = d->m_itemData.size(); column < count; ++column)
    {
        d->m_itemData.append(QVariant());
        d->m_itemRoleData.append(QHash<int ,QVariant>());
        d->m_background.append(Qt::white);
        d->m_foreground.append(Qt::black);
    }

    removeColumns(count - 1,d->m_itemData.size() - count);
}

QVariant EGridItem::data(int column,int role) const
{
    Q_D(const EGridItem);

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


EGridItem* EGridItem::parent() const
{
    Q_D(const EGridItem);
    return d->m_parentItem;
}

void EGridItem::setParent(EGridItem *parent)
{
    Q_D(EGridItem);
    d->m_parentItem = parent;
}

int EGridItem::row() const
{
    Q_D(const EGridItem);
    if(d->m_parentItem)
        return d->m_parentItem->children().indexOf(const_cast<EGridItem *>(this));

    return 0;
}

bool EGridItem::insertChildren(int row, int count)
{
    Q_D(EGridItem);
    if(row < 0 || row > d->m_childItems.size())
        return false;

    for(int tempRow = 0; tempRow < count; ++tempRow)
    {
        EGridItem *item = new EGridItem(this);
        item->setColumnCount(this->columnCount());
        d->m_childItems.insert(row,item);
    }

    return true;
}


bool EGridItem::insertColumns(int column, int count)
{
    Q_D(EGridItem);

    for(int tempColumn = 0; tempColumn < count; ++tempColumn)
    {
        d->m_itemData.insert(column,QVariant());
        d->m_itemRoleData.insert(column,QHash<int ,QVariant>());
    }

    for(auto *child : qAsConst(d->m_childItems))
        child->insertColumns(column,count);

    return true;
}


bool EGridItem::removeChildren(int column, int count)
{
    Q_D(EGridItem);
    if(column < 0 || column + count > d->m_itemData.size())
        return false;

    for(int row = 0; row < count; ++row)
        delete d->m_childItems.takeAt(column);

    return true;
}

bool EGridItem::removeColumns(int column, int count)
{
    Q_D(EGridItem);
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

bool EGridItem::setData(int column, const QVariant &value,int role)
{
    Q_D(EGridItem);

    if(column < 0)
        return false;

    bool flag = false;
    do{
        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:{

            if(column >= d->m_itemData.size())
            {
                for(int i = d->m_itemData.size() - 1; i < column - 1; ++i)
                {
                    d->m_itemData.append(QVariant());
                }

                d->m_itemData.append(value);
            }
            else if(d->m_itemData[column] != value)
            {
                d->m_itemData[column] = value;
            }
            else
            {
                break;//unchanged
            }

            flag = true;
        }break;
        default:{
            if(column < 0 || column >= d->m_itemRoleData.size())
                break;
            flag = true;
            d->m_itemRoleData[column][role] = value;
        }break;
        }
    }while(false);

    return flag;
}

void EGridItem::setProperty(const QString &name, const QVariant &value)
{
    Q_D(EGridItem);

    d->m_propertyToValue[name] = value;
}

QVariant EGridItem::property(const QString &name)
{
    Q_D(const EGridItem);

    return d->m_propertyToValue.value(name,name);
}
