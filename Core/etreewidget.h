#ifndef ETREEWIDGET_H
#define ETREEWIDGET_H

#include "core_global.h"
#include <QTreeView>

class CORE_EXPORT ETreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit ETreeWidget(QTreeView *parent = nullptr);

    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const override;

    /**
     * @brief drawStatLabel
     * 绘制状态标签
     * @param painter
     * @param options
     * @param index
     */
    void drawStateLabel(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
};

#endif // ETREEWIDGET_H
