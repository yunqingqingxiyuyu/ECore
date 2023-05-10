#ifndef ETREEMODEL_H
#define ETREEMODEL_H

#include "core_global.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class EWidgetItem;

class CORE_EXPORT ETreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ETreeModel(QObject *parent = nullptr);
    virtual ~ETreeModel();

    /**
     * @brief columnCount
     * @param parent
     * @return 返回列的数量
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief rowCount
     * @param parent
     * @return 返回行数量
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief data
     * @param index
     * @param role
     * @return 返回index的role角色对应的数据
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief flags
     * @param index
     * @return 返回index对应的标志
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief getItem
     * @param index
     * @return 返回index对应的item
     */
    EWidgetItem* getItem(const QModelIndex &index) const;

    /**
     * @brief headerData
     * @param section
     * @param orientation
     * @param role
     * @return 返回secion列表头role角色对应的数据
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * @brief index
     * @param row
     * @param column
     * @param parent
     * @return
     */
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;


    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QModelIndex parent(const QModelIndex &child) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    void setupModelData(const QJsonArray &array);
private:
    EWidgetItem *m_rootItem = nullptr;
};

#endif // ETREEMODEL_H
