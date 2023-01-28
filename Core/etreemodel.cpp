#include "etreemodel.h"
#include "etreeitem.h"

#include <QJsonObject>
#include <QJsonArray>

ETreeModel::ETreeModel(QObject *parent):
    QAbstractItemModel(parent)
{

}

ETreeModel::~ETreeModel()
{

}


int ETreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rootItem->columnCount();
}

QVariant ETreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    ETreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags ETreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

ETreeItem *ETreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        ETreeItem *item = static_cast<ETreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}

QVariant ETreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data(section);

    return QVariant();
}

QModelIndex ETreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    ETreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    ETreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

bool ETreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = m_rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool ETreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    ETreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    m_rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex ETreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ETreeItem *childItem = getItem(index);
    ETreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == m_rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool ETreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = m_rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (m_rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool ETreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    ETreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int ETreeModel::rowCount(const QModelIndex &parent) const
{
    const ETreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}

bool ETreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    ETreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool ETreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = m_rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}


void ETreeModel::setupModelData(const QStringList &lines, ETreeItem *parent)
{
    QVector<ETreeItem*> parents;
    QVector<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            columnData.reserve(columnStrings.size());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            ETreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, m_rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }
        ++number;
    }
}

void ETreeModel::setupModelData(const QJsonValue &obj,
                                ETreeItem *parent,
                                const QString &tagIdName,
                                const QString &tagName)
{
    QJsonArray array = obj.toArray();

    ETreeItem *newItem = nullptr;
    for(int count = 0; count < array.size(); ++count)
    {
        QJsonObject obj = array.at(count).toObject();

        auto tagID = obj.value(tagIdName).toVariant();
        auto name = obj.value(tagName).toVariant();

        QVector<QVariant> rowData;
        rowData << name;
        newItem = new ETreeItem(rowData);
        newItem->setData(ETreeItem::TagID,tagID);
        newItem->setData(ETreeItem::TagName,tagName);
    }
}
