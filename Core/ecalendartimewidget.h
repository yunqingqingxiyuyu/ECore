#ifndef ECALENDARTIMEWIDGET_H
#define ECALENDARTIMEWIDGET_H

#include "core_global.h"

#include <QCalendarWidget>

class CORE_EXPORT ECalendarTimeWidget : public QCalendarWidget
{
    Q_OBJECT

public:
    explicit ECalendarTimeWidget(QWidget *parent = nullptr);
    virtual ~ECalendarTimeWidget();

    QSize sizeHint() const override;

private:
    Q_DISABLE_COPY(ECalendarTimeWidget);
    Q_DECLARE_D(ECalendarTimeWidget);
    Q_DECLARE_PRIVATE(ECalendarTimeWidget);

};

#endif // ECALENDARTIMEWIDGET_H
