#ifndef ETREEWIDGET_H
#define ETREEWIDGET_H

#include "core_global.h"
#include <QTreeView>

class CORE_EXPORT ETreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit ETreeWidget(QTreeView *parent = nullptr);

    /**
     * @brief setLabelFont
     * 设置标签的字体大小
     */
    void setLabelFont(const QFont &font){m_labelFont = font;}

    /**
     * @brief labelFont
     * @return 返回标签的字体大小
     */
    QFont labelFont() const {return m_labelFont;}

    /**
     * @brief setLabelAligment
     *
     */
    void setLabelAligment(int align){m_labelAligment = align;}

    /**
     * @brief labelAlignment
     * @return 返回标签的对齐方式
     */
    int labelAlignment() const {return m_labelAligment;}

    /**
     * @brief setLabelFormat
     * 设置标签的显示格式
     * @param format
     */
    void setLabelFormat(const QString &format);
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
    QFont m_labelFont;

    int m_labelAligment = Qt::AlignLeft;

};

#endif // ETREEWIDGET_H
