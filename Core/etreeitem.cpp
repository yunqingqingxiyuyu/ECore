#include "etreeitem.h"

ETreeItem::ETreeItem(const QVector<QVariant> &data,
                   ETreeItem *parent)
    : m_itemData(data),
      m_parentItem(parent)
{

}


ETreeItem::~ETreeItem()
{
    qDeleteAll(m_childItems);
}

ETreeItem *ETreeItem::child(int number)
{
    if (number < 0 || number >= m_childItems.size())
        return nullptr;
    return m_childItems.at(number);
}

int ETreeItem::childCount() const
{
    return m_childItems.count();
}

int ETreeItem::childNumber() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ETreeItem*>(this));
    return 0;
}

int ETreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant ETreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

bool ETreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        ETreeItem *item = new ETreeItem(data, this);
        m_childItems.insert(position, item);
    }

    return true;
}

bool ETreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.insert(position, QVariant());

    for (ETreeItem *child : qAsConst(m_childItems))
        child->insertColumns(position, columns);

    return true;
}

ETreeItem *ETreeItem::parent() const
{
    return m_parentItem;
}

bool ETreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);

    return true;
}

bool ETreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.remove(position);

    for (ETreeItem *child : qAsConst(m_childItems))
        child->removeColumns(position, columns);

    return true;
}

bool ETreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.size())
        return false;

    m_itemData[column] = value;
    return true;
}

bool ETreeItem::setStateData(int column,const QMap<QString ,QVariant> &states)
{
    if(column < 0 || column >= m_itemData.size())
        return false;
    m_stateData[column] = states;
    return true;
}

bool ETreeItem::setStateData(int column,const QString &stateName,const QVariant &state)
{
    if(column < 0 || column >= m_itemData.size())
        return false;
    m_stateData[column].insert(stateName,state);
    return true;
}

bool ETreeItem::clearStateData(int column)
{
    if(column < 0 || column >= m_itemData.size())
        return false;
    m_stateData[column].clear();
    return true;
}

QMap<QString,QVariant> ETreeItem::stateData(int column)
{
    if(column < 0 || column >= m_itemData.size())
        return QMap<QString,QVariant>{{"",QVariant()}};
    return m_stateData[column];
}

QVariant ETreeItem::stateData(int column,const QString &stateName)
{
    if(column < 0 || column >= m_itemData.size())
        return QVariant();

    return m_stateData[column][stateName];
}

