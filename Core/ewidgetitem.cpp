#include "ewidgetitem.h"

#include "ewidgetitem_p.h"

EWidgetItem::EWidgetItem(const QVector<QVariant > &data,EWidgetItem *parent):
    d_ptr(new EWidgetItemPrivate(this)),
    m_itemData(data),
    m_parentItem(parent)
{
}

EWidgetItem::~EWidgetItem()
{
    qDeleteAll(m_childItems);
}

EWidgetItem* EWidgetItem::child(int number) const
{
    if(number < 0 || number >= m_childItems.size())
        return nullptr;

    return m_childItems.at(number);
}

int EWidgetItem::childCount() const
{
    return m_childItems.size();
}

int EWidgetItem::indexOfParent() const
{
    if(m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<EWidgetItem *>(this));
    return 0;
}

int EWidgetItem::colmnCount() const
{
    return m_itemData.count();
}

//todo 需要设置TOOLTIP等属性
QVariant EWidgetItem::data(int column,int role) const
{
    Q_UNUSED(role);
    if(column < 0 || column >= m_itemData.size())
        return QVariant();

    return m_itemData.at(column);
}
