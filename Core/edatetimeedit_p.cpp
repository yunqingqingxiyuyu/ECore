#include "edatetimeedit_p.h"

#include "edatetimeedit.h"

#include <QDebug>
#include "ecalendartimewidget.h"

EDateTimeEditPrivate::EDateTimeEditPrivate(EDateTimeEdit *parent):
    q_ptr(parent)
{
    Q_Q(EDateTimeEdit);
    lineEdit = q->QDateTimeEdit::lineEdit();
}


void EDateTimeEditPrivate::setCalendarTimeWidget(ECalendarTimeWidget *calendarTimeWidget)
{
    Q_Q(EDateTimeEdit);
    if(!q->QDateTimeEdit::calendarPopup())
    {
        return;
    }
    if(m_calendarTimeWidget)
    {
        m_calendarTimeWidget->deleteLater();
    }
    m_calendarTimeWidget = calendarTimeWidget;

    if(m_calendarTimeWidget)
    {
        if(m_selectedDate.isValid())
            m_calendarTimeWidget->setSelectedDateTime(m_selectedDate);
        m_calendarTimeWidget->setDateTimeRange(m_minDateTime,m_maxDateTime);
    }

    q->QDateTimeEdit::setCalendarWidget(calendarTimeWidget);
}

void EDateTimeEditPrivate::setMaximumDateTime(const QDateTime &dateTime)
{
    Q_Q(EDateTimeEdit);
    if(m_calendarTimeWidget)
    {
        m_calendarTimeWidget->setMaximumDateTime(dateTime);
    }

    q->QDateTimeEdit::setMaximumDate(dateTime.date());
    m_maxDateTime = dateTime;
}

void EDateTimeEditPrivate::setMinimumDateTime(const QDateTime &dateTime)
{
    Q_Q(EDateTimeEdit);
    if(m_calendarTimeWidget)
    {
        m_calendarTimeWidget->setMinimumDateTime(dateTime);
    }

    q->QDateTimeEdit::setMinimumDate(dateTime.date());

    m_minDateTime = dateTime;
}

void EDateTimeEditPrivate::setSelectedDateTime(const QDateTime &dateTime)
{
    if(m_calendarTimeWidget)
    {
        m_calendarTimeWidget->setSelectedDateTime(dateTime);
    }

    m_selectedDate = dateTime;
}
