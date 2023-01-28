#ifndef ETREEMODEL_H
#define ETREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ETreeItem;

/**
 * @brief The ETreeModel class
 * @details 传入json,自动获取其tagID,与tagName构建文件树
 */
class ETreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ETreeModel(QObject *parent = nullptr);
    virtual ~ETreeModel();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:

    ETreeItem* getItem(const QModelIndex &index) const;
    void setupModelData(const QStringList &lines, ETreeItem *parent);
    void setupModelData(const QJsonValue &obj,
                        ETreeItem *parent,
                        const QString &tagIdName = "",
                        const QString &tagName = "");
private:
    ETreeItem *m_rootItem = nullptr;
};

#endif // TREEMODEL_H
