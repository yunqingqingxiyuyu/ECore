#ifndef ECALENDARTIMEWIDGETPRIVATE_H
#define ECALENDARTIMEWIDGETPRIVATE_H

#include <QObject>

class ECalendarTimeWidget;
class ETimeWidget;

class ECalendarTimeWidgetPrivate : public QObject
{
    Q_OBJECT
    ECalendarTimeWidget *const q_ptr;
    Q_DISABLE_COPY(ECalendarTimeWidgetPrivate);
    Q_DECLARE_PUBLIC(ECalendarTimeWidget);

public:
    explicit ECalendarTimeWidgetPrivate(ECalendarTimeWidget *parent);

private:
    QWidget* timeWidget() const;

public:
    ETimeWidget *m_timeWidget = nullptr;

};

#endif // ECALENDARTIMEWIDGETPRIVATE_H
