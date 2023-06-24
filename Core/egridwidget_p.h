#ifndef EGRIDWIDGETPRIVATE_H
#define EGRIDWIDGETPRIVATE_H

#include <QObject>
#include <QFont>

class EGridWidget;
class QHeaderView;

class EGridWidgetPrivate : public QObject
{
    Q_OBJECT

    EGridWidget * const q_ptr;
    Q_DISABLE_COPY(EGridWidgetPrivate);
    Q_DECLARE_PUBLIC(EGridWidget);

public:
    explicit EGridWidgetPrivate(EGridWidget *parent);
    ~EGridWidgetPrivate();

private:
    QFont labelFont;
    int labelAligment = Qt::AlignLeft;
    QHeaderView *verticalHeader = nullptr;
};

#endif // ETREEWIDGETPRIVATE_H
