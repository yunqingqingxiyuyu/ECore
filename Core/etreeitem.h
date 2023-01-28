#ifndef ETREEITEM_H
#define ETREEITEM_H

#include <QVariant>
#include <QVector>

class ETreeItem
{
public:

    enum ItemDataRole{
        TagID = Qt::UserRole,
        TagName = Qt::DisplayRole
    };

    //定义状态类型
    enum StateType{
        String = Qt::UserRole + 1,
        Icon
    };

    //定义状态信息
    typedef struct StateInfo{
        QString content;//状态显示内容
        QString toopTip;//状态的提示
        ETreeItem::StateType type;
    }StateInfo;

    explicit ETreeItem(const QVector<QVariant> &data, ETreeItem *parent = nullptr);
    ~ETreeItem();

    ETreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    ETreeItem *parent() const;
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

    /**
     * @brief setStateData
     * 设置column列的状态，设置成功返回true,否则返回false
     * @param column 列序号
     * @param states 状态
     * @return 设置成功返回true
     */
    bool setStateData(int column,const QMap<QString ,QVariant> &states);

    /**
     * @brief setStateData
     * @param column 列
     * @param stateName 状态名
     * @param state 状态信息
     * @return 设置成功返回true,否则返回false
     */
    bool setStateData(int column,const QString &stateName,const QVariant &state);

    /**
     * @brief clearStateData
     * 清空column列的状态
     * @param column 列序号
     * @return 成功返回true
     */
    bool clearStateData(int column);

    /**
     * @brief stateData
     * @param column
     * @return 返回column列的当前显示状态
     */
    QMap<QString,QVariant> stateData(int column);

    /**
     * @brief stateData
     * @param column
     * @param stateName 状态名
     * @return 返回column某状态的内容，没有则返回QVariant()
     */
    QVariant stateData(int column,const QString &stateName);

private:
    QVector<ETreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    QVector<QMap<QString,QVariant>> m_stateData;
    ETreeItem *m_parentItem = nullptr;
};

Q_DECLARE_METATYPE(ETreeItem::StateInfo);

#endif // TREEITEM_H
