#include "egridmodel.h"

#include "egriditem.h"

#include <QJsonArray>
#include <QDebug>
#include <QJsonObject>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

EGridModel::EGridModel(int columns,QObject *parent):
    QAbstractItemModel(parent)
{
    QVector<QVariant> va{tr("Title"), tr("Summary")};
    m_rootItem = new EGridItem();
    m_rootItem->setColumnCount(columns);
}

EGridModel::~EGridModel()
{
    delete m_rootItem;
}

int EGridModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return static_cast<EGridItem *>(parent.internalPointer())->columnCount();
    return m_rootItem->columnCount();
}

int EGridModel::rowCount(const QModelIndex &parent) const
{
    EGridItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<EGridItem*>(parent.internalPointer());

    if(parentItem)
        return parentItem->childCount();
    else
        return m_rootItem->childCount();
}

QVariant EGridModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch (role) {
    case Ex::IndentLevel:
    case Qt::DisplayRole:
    case Qt::EditRole:
    {
        auto *item = static_cast<EGridItem *>(index.internalPointer());
        return item->data(index.column(),role);
        break;
    }
    case Ex::Label:
    {
        return label(index);
    }
    default:
        return QVariant();
    }
}

Qt::ItemFlags EGridModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

EGridItem* EGridModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        EGridItem *item = static_cast<EGridItem*>(index.internalPointer());
        if (item)
            return item;
        return nullptr;
    }
    return m_rootItem;
}

QVariant EGridModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && m_rootItem)
        return m_rootItem->data(section,role);

    return QVariant();
}


QModelIndex EGridModel::index(int row, int column, const QModelIndex &parent) const
{
    EGridItem *parentItem = getItem(parent);
    if(!parentItem)
        return QModelIndex();

    EGridItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem);

    return QModelIndex();
}

bool EGridModel::insertRows(int row, int count, const QModelIndex &parent)
{
    EGridItem *parentItem = getItem(parent);
    if(!parentItem)
        return false;

    beginInsertRows(parent,row,row + count - 1);

    const bool success = parentItem->insertChildren(row,
                                               count
                                               );

    endInsertRows();
    return success;
}

bool EGridModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent,column,column + count -1);
    const bool success = m_rootItem->insertColumns(column,count);
    endInsertColumns();

    return success;
}

QModelIndex EGridModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    EGridItem *childItem = getItem(child);
    EGridItem *parentItem = childItem ? childItem->parent() : nullptr;
    if(parentItem == m_rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->indexOfParent(),0,parentItem);
}

bool EGridModel::removeRows(int row, int count, const QModelIndex &parent)
{
    auto *parentItem = getItem(parent);
    if(!parentItem)
        return false;
    beginRemoveRows(parent,row,row + count -1);
    const bool success = parentItem->removeChildren(row,count);

    endRemoveRows();

    return success;
}

bool EGridModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent,column,column + count -1);
    const bool success = m_rootItem->removeColumns(column,count);
    endRemoveColumns();

    if(m_rootItem && m_rootItem->columnCount() == 0)
        removeRows(0 , rowCount());

    return success;
}

bool EGridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    EGridItem *item = getItem(index);
    bool result = item->setData(index.column(),value);

    if(result)
        emit dataChanged(index,index,{Qt::EditRole , Qt::DisplayRole});

    return result;
}

bool EGridModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = m_rootItem->setData(section,value);

    if(result)
        emit headerDataChanged(orientation,section,section);

    return result;
}

void EGridModel::setupModelData(const QJsonArray &array)
{
    setupModelData(array,m_rootItem);
}


void EGridModel::setupModelData(const QJsonArray &array, EGridItem *parentItem)
{
    int columnCount = 1;
    if(parentItem)
        columnCount = parentItem->columnCount();

    for(int row = 0; row < array.size(); ++row)
    {
        QJsonObject temp = array.at(row).toObject();

        auto *newItem = new EGridItem();
        newItem->setColumnCount(columnCount);
        for(auto iter = propertyToAlias.constBegin(); iter != propertyToAlias.constEnd(); ++iter)
        {
            QString propery = iter.key();
            QString alias = iter.value();

            if(alias.isEmpty())
                continue;

            if(propery == "content")
            {
                newItem->setData(0,temp.value(alias).toVariant());
                newItem->setData(1,QString("%1%2").arg(temp.value(alias).toVariant().toString(),"///"));
            }
            else if(propery == "children")
            {
                setupModelData(temp.value(alias).toArray(),newItem);
            }
        }

        for(auto &&alias : propertyAlias)
        {
            newItem->setProperty(0,alias,temp.value(alias).toVariant());
            newItem->setProperty(1,alias,temp.value(alias).toVariant());
        }

        parentItem->appendChild(newItem);
    }
}

QString EGridModel::label(const QModelIndex &index) const
{
    auto *item = static_cast<EGridItem *>(index.internalPointer());
    if(!item)
        return m_labelFormat;

    QString format = m_labelFormat;

    QRegularExpression re("\\[([^\\[\\]]*?)\\]");
    QRegularExpressionMatchIterator matchIter = re.globalMatch(format);

    QHash<QString ,QString> result;
    while(matchIter.hasNext())
    {
        QRegularExpressionMatch match = matchIter.next();

        result.insert(match.captured(1),item->property(index.column(),match.captured(1)).toString());
    }

    for(auto iter = result.constBegin(); iter != result.constEnd(); ++iter)
    {
        format.replace(QString("[%1]").arg(iter.key()),iter.value());
    }

    return format;
}
