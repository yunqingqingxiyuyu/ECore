#ifndef EWIDGETITEM_H
#define EWIDGETITEM_H

#include "core_global.h"
#include <QVariant>
#include <QVector>

class EWidgetItemPrivate;
class ETreeModel;
class ETreeWidget;

class CORE_EXPORT EWidgetItem
{
public:
    enum ItemType{Type = 0, UserType = 1000};

    explicit EWidgetItem(EWidgetItem *parent = nullptr);
    explicit EWidgetItem(int type,EWidgetItem *parent = nullptr);
    explicit EWidgetItem(const QStringList &strings,int type,EWidgetItem *parent = nullptr);
    ~EWidgetItem();

    /**
     * @brief addChild
     * @param item
     */
    void addChild(EWidgetItem *item);

    /**
     * @brief appendChildd
     * 添加子节点
     * @param item
     */
    void appendChild(EWidgetItem *item);

    /**
     * @brief appendChildren
     * 添加子节点
     * @param children
     */
    void appendChildren(const QVector<EWidgetItem *> &childre);

    /**
     * @brief background
     * @return 返回column列的brush
     */
    QBrush backgroundBrush(int column) const;

    /**
     * @brief setBackgroun
     * 设置columnn列的背景brush
     * @param column
     * @param brush
     */
    void setBackgroudBrush(int column , const QBrush	&brush);


    /**
     * @brief forebackgroundBrush
     * @param column
     * @return
     */
    QBrush forebackgroundBrush(int column) const;

    /**
     * @brief setForebackgroundBrush
     * @param column
     * @param brush
     */
    void setForebackgroundBrush(int column , const QBrush &brush);

    /**
     * @brief child
     * @param number
     * @return 返回number的子节点，如果number位置的节点不存在则返回nullptr。
     */
    EWidgetItem* child(int number) const;

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
    int columnCount() const;

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
    bool setData(int column, const QVariant &variant,int role = Qt::DisplayRole);


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


    /**
     * @brief setProperty
     * @param name 属性名
     * @param value 值
     */
    void setProperty(int column ,const QString &name,const QVariant &value);

    /**
     * @brief property
     * 获取熟悉内容
     * @param column
     * @param name
     * @return
     */
    QVariant property(int column,const QString &name);


    /**
     * @brief setIndentLevel
     * 设置缩进等级
     * @param level
     */
    void setIndentLevel(int level);

    /**
     * @brief setSelected
     * 设置item为select的选择状态
     * @param select
     */
    void setSelected(bool select);

    /**
     * @brief model
     * 如果设置了view则返回其模型
     * @param v
     * @return
     */
    ETreeModel* model(ETreeWidget *v = nullptr) const;

    void setText(int column,const QString &text);

private:

private:
    Q_DECLARE_D(EWidgetItem);
    Q_DECLARE_PRIVATE(EWidgetItem);

    int rtti = 0;
    Qt::ItemFlags itemFlags;
    ETreeWidget *view = nullptr;
};

inline
void EWidgetItem::setText(int column, const QString &text)
{
    setData(column,Qt::DisplayRole,text);
}

#endif // EWIDGETITEM_H
