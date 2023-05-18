#include "etreewidget.h"
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QFontMetrics>

#include <EWidgetItem>

ETreeWidget::ETreeWidget(QTreeView * parent):
    QTreeView(parent)
{

}

void ETreeWidget::drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    QTreeView::drawRow(painter,options,index);
    drawStateLabel(painter,options,index);
}

void ETreeWidget::drawStateLabel(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    painter->save();

    int row = index.row();
    QFont font = options.font;

    qDebug() << __PRETTY_FUNCTION__ << index.data();
    for(int column = 0; column < model()->columnCount(); ++column)
    {
        auto index = model()->index(row,column);
        QString stateLabel = index.data(Qt::UserRole + 1).toString();
        QString content = index.data().toString();
        QFontMetrics met(font);
        QRect rect = options.rect;
        rect.setX(this->header()->sectionPosition(column));
        rect.setWidth(columnWidth(column));

        int offsetX = met.horizontalAdvance(content);
        stateLabel = "[label][from郑龙]";
        qDebug() << offsetX << content;
        painter->drawText(rect.adjusted(offsetX,0,0,0),Qt::AlignRight,stateLabel);
    }
    painter->restore();
}

