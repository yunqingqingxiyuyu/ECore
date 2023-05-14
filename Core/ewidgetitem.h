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

    explicit EWidgetItem(EWidgetItem *parent = nullptr);
    ~EWidgetItem();

    /**
     * @brief child
     * @param number
     * @return 返回number的子节点，如果number位置的节点不存在则返回nullptr。
     */
    EWidgetItem* child(int number) const;

    /**
     * @brief appendChildd
     * 添加子节点
     * @param item
     */
    void appendChild(EWidgetItem *item);

    /**
     * @brief children
     * @return 孩子对象
     */
    QVector<EWidgetItem *> children() const;

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
     * @brief setColumnCount
     * 设置列的数量
     * @param count
     */
    void setColumnCount(int count);


    /**
     * @brief data
     * @param column
     * @return 返回column的数据
     */
    QVariant data(int column,int role = Qt::DisplayRole) const;


    /**
     * @brief parent
     * @return 返回父节点
     */
    EWidgetItem* parent() const;

    /**
     * @brief setParent
     * 设置父节点
     * @param parent
     */
    void setParent(EWidgetItem *parent);

    /**
     * @brief row
     * @return
     */
    int row() const;

    /**
     * @brief insertChilder
     * @param row
     * @param count
     * @return
     */
    bool insertChildren(int row,int count);

    /**
     * @brief insertColumns
     * @param column
     * @param count
     * @return
     */
    bool insertColumns(int column,int count);

    /**
     * @brief removeChild
     * @param column
     * @param count
     * @return
     */
    bool removeChildren(int column,int count);

    /**
     * @brief removeColumns
     * @param column
     * @param count
     * @return
     */
    bool removeColumns(int column,int count);

    bool setData(int column, const QVariant &variant,int role = Qt::DisplayRole);
private:
    Q_DECLARE_D(EWidgetItem);
    Q_DECLARE_PRIVATE(EWidgetItem);
};

#endif // EWIDGETITEM_H
