#include "ecalendartimewidget_p.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTime>

#include "etimewidget.h"

ECalendarTimeWidgetPrivate::ECalendarTimeWidgetPrivate(ECalendarTimeWidget *parent):
    q_ptr(parent)
{
    m_timeWidget = new ETimeWidget(QTime::currentTime());
}

QWidget* ECalendarTimeWidgetPrivate::timeWidget() const
{
    return m_timeWidget;
}
