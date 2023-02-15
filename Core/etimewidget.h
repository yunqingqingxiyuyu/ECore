#ifndef ETIMEWIDGET_H
#define ETIMEWIDGET_H

#include "core_global.h"

#include <QWidget>

class ETimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ETimeWidget(const QTime &time,QWidget *parent = nullptr);
    ~ETimeWidget();



private:
    Q_DISABLE_COPY(ETimeWidget);
    Q_DECLARE_D(ETimeWidget);
    Q_DECLARE_PRIVATE(ETimeWidget);
};

#endif // ETIMEWIDGET_H
