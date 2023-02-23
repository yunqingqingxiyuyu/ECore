#include "ecalendartimewidget_p.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTime>

#include "etimewidget.h"

ECalendarTimeWidgetPrivate::ECalendarTimeWidgetPrivate(ECalendarTimeWidget *parent):
    q_ptr(parent)
{
    Q_Q(ECalendarTimeWidget);

    m_timeWidget = new ETimeWidget(QTime::currentTime());
}

QWidget* ECalendarTimeWidgetPrivate::timeWidget() const
{
    return m_timeWidget;
}

void ECalendarTimeWidgetPrivate::setDateTime(const QDateTime &dateTime)
{
    m_timeWidget->setTime(dateTime.time());
}

QTime ECalendarTimeWidgetPrivate::time() const
{
    return m_timeWidget->time();
}
