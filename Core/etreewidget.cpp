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
    //绘制网格线
    QPen pen;

    painter->save();
    painter->setPen(pen);
    painter->drawRect(options.rect);
    painter->restore();

    int row = index.row();
    QFont font = options.font;

    for(int column = 0; column < model()->columnCount(); ++column)
    {
        auto index = model()->index(row,column);
        QString stateLabel = index.data(Ex::Label).toString();
        QString content = index.data().toString();
        QFontMetrics met(font);
        QRect rect = options.rect;
        rect.setX(this->header()->sectionPosition(column));
        rect.setWidth(columnWidth(column));

        int indentWidth = indentation() * index.data(Ex::IndentLevel).toInt();
        int offsetX = met.horizontalAdvance(content) + indentWidth;
        stateLabel = "[label][from郑龙]" ;
        painter->drawText(rect.adjusted(offsetX,0,0,0),Qt::AlignLeft,stateLabel);
    }
    painter->restore();
}

