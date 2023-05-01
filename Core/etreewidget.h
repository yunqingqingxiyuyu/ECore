#ifndef ETREEWIDGET_H
#define ETREEWIDGET_H

#include <QTreeView>


class ETreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit ETreeWidget(QTreeView *parent = nullptr);
};

#endif // ETREEWIDGET_H
