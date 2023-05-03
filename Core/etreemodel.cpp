#include "etreemodel.h"

#include "ewidgetitem.h"

#include <QJsonArray>
#include <QJsonObject>

ETreeModel::ETreeModel(QObject *parent):
    QAbstractItemModel(parent)
{

}

ETreeModel::~ETreeModel()
{
    delete m_rootItem;
}

int ETreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rootItem->colmnCount();
}

QVariant ETreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
    {
        break;
    }
    }

    return QVariant();
}

Qt::ItemFlags ETreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

EWidgetItem* ETreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        EWidgetItem *item = static_cast<EWidgetItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}

QVariant ETreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(m_rootItem)
        return m_rootItem->data(section,role);
    return QVariant();
}


QModelIndex ETreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() && parent.column() !=0)
        return QModelIndex();

    EWidgetItem *parentItem = getItem(parent);
    if(!parentItem)
        return QModelIndex();

    EWidgetItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem);

    return QModelIndex();
}

bool ETreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    EWidgetItem *parentItem = getItem(parent);
    if(!parentItem)
        return false;

    beginInsertRows(parent,row,row + count - 1);

    const bool success = parentItem->insertChildren(row,
                                               count,
                                               m_rootItem->colmnCount());

    endInsertRows();

    return success;
}

bool ETreeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent,column,column + count -1);
    const bool success = m_rootItem->insertColumns(column,count);
    endInsertColumns();

    return success;
}

QModelIndex ETreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    EWidgetItem *childItem = getItem(child);
    EWidgetItem *parentItem = childItem ? childItem->parent() : nullptr;
    if(parentItem == m_rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->indexOfParent(),0,parentItem);
}

bool ETreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    auto *parentItem = getItem(parent);
    if(!parentItem)
        return false;
    beginRemoveRows(parent,row,row + count -1);
    const bool success = parentItem->removeChildren(row,count);

    endRemoveRows();

    return success;
}

bool ETreeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent,column,column + count -1);
    const bool success = m_rootItem->removeColumns(column,count);
    endRemoveColumns();

    if(m_rootItem->colmnCount() == 0)
        removeRows(0 , rowCount());

    return success;
}

bool ETreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    EWidgetItem *item = getItem(index);
    bool result = item->setData(index.column(),value);

    if(result)
        emit dataChanged(index,index,{Qt::EditRole , Qt::DisplayRole});

    return result;
}

bool ETreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = m_rootItem->setData(section,value);

    if(result)
        emit headerDataChanged(orientation,section,section);

    return result;
}

void ETreeModel::setupModelData(const QJsonArray &array)
{
    QMap<QString ,EWidgetItem *> topItems;
    for(int row = 0; row < array.size(); ++row)
    {
        QJsonObject temp = array.at(row).toObject();
        QString parentID = temp.value("parentId").toString();
        QString id = temp.value("id").toString();
        QString content = temp.value("content").toString();

        auto parentItem = topItems.value(parentID,nullptr);
        if(parentItem)
            parentItem->insertChildren(parentItem->childCount(),1,m_rootItem->colmnCount());
    }
}
