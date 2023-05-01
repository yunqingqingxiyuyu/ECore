#ifndef EWIDGETITEM_H
#define EWIDGETITEM_H

#include "core_global.h"
#include <QVariant>
#include <QVector>

class EWidgetItemPrivate;


class CORE_EXPORT EWidgetItem
{
public:
    enum ItemType{Type = 0, UserType = 1000};

    explicit EWidgetItem(const QVector<QVariant > &datam,EWidgetItem *parent);
    ~EWidgetItem();

    /**
     * @brief child
     * @param number
     * @return 返回number的子节点，如果number位置的节点不存在则返回nullptr。
     */
    EWidgetItem* child(int number) const;

    /**
     * @brief childCount
     * @return 返回子节点的个数
     */
    int childCount() const;

    /**
     * @brief indexOfParent
     * @return 当前节点在父节点中的索引位置
     */
    int indexOfParent() const;

    /**
     * @brief colmnCount
     * @return 返回列数量
     */
    int colmnCount() const;


    /**
     * @brief data
     * @param column
     * @return 返回column的数据
     */
    QVariant data(int column,int role) const;




private:
    Q_DECLARE_D(EWidgetItem);
    Q_DECLARE_PRIVATE(EWidgetItem);
    QVector<EWidgetItem*> m_childItems;
    QVector<QVariant> m_itemData;
    EWidgetItem *m_parentItem;
};

#endif // EWIDGETITEM_H
