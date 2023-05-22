#include "etreewidget.h"
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QFontMetrics>

#include <EWidgetItem>

ETreeWidget::ETreeWidget(QTreeView * parent):
    QTreeView(parent),
    m_labelFont(font())
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

    QFont font = options.font;
    int row = index.row();

    for(int column = 0; column < model()->columnCount(); ++column)
    {
        QModelIndex currentIndex = model()->index(row,column,index.parent());
        QString stateLabel = currentIndex.data(Ex::Label).toString();
        QString content = currentIndex.data().toString();
        QFontMetrics met(font);
        QRect rect = options.rect;
        rect.setX(this->header()->sectionPosition(column));
        rect.setWidth(columnWidth(column));

        int indentWidth = indentation() * currentIndex.data(Ex::IndentLevel).toInt();
        int offsetX = met.horizontalAdvance(content) + indentWidth + 6;
        stateLabel = "[label][from郑龙]" ;
        qDebug() << currentIndex.data() << currentIndex.row() << currentIndex.column() << column << currentIndex.data(Ex::IndentLevel) << currentIndex.data();
        painter->setFont(labelFont());
        painter->drawText(rect.adjusted(offsetX,0,0,0),labelAlignment(),stateLabel);
    }
    painter->restore();
}

