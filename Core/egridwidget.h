#ifndef EGRIDWIDGET_H
#define EGRIDWIDGET_H

#include "core_global.h"
#include <QTreeView>

class EGridWidgetPrivate;

class CORE_EXPORT EGridWidget : public QTreeView
{
    Q_OBJECT

    Q_DISABLE_COPY(EGridWidget);
    Q_DECLARE_D(EGridWidget);
    Q_DECLARE_PRIVATE(EGridWidget);

public:
    explicit EGridWidget(QWidget *parent = nullptr);

    /**
     * @brief setLabelFont
     * 设置标签的字体大小
     */
    void setLabelFont(const QFont &font);

    /**
     * @brief labelFont
     * @return 返回标签的字体大小
     */
    QFont labelFont() const;

    /**
     * @brief setLabelAligment
     *
     */
    void setLabelAligment(int align);

    /**
     * @brief labelAlignment
     * @return 返回标签的对齐方式
     */
    int labelAlignment() const;

    /**
     * @brief setLabelFormat
     * 设置标签的显示格式
     * @param format
     */
    void setLabelFormat(int column,const QString &format);


protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const override;

    /**
     * @brief drawStatLabel
     * 绘制状态标签
     * @param painter
     * @param options
     * @param index
     */
    void drawStateLabel(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;

private:
};

#endif // ETREEWIDGET_H
