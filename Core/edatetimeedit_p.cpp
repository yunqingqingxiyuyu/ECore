#include "edatetimeedit_p.h"

#include "edatetimeedit.h"

#include <QDebug>
#include "ecalendartimewidget.h"

EDateTimeEditPrivate::EDateTimeEditPrivate(EDateTimeEdit *parent):
    q_ptr(parent)
{
    Q_Q(EDateTimeEdit);
    lineEdit = q->QDateTimeEdit::lineEdit();

    m_calendarTimeWidget = new ECalendarTimeWidget;
    q->QDateTimeEdit::setCalendarWidget(m_calendarTimeWidget);
}


void EDateTimeEditPrivate::setCalendarTimeWidget(ECalendarTimeWidget *calendarTimeWidget)
{
    Q_Q(EDateTimeEdit);
    m_calendarTimeWidget = calendarTimeWidget;

    if(m_calendarTimeWidget)
    {
    }

    q->QDateTimeEdit::setCalendarWidget(calendarTimeWidget);
}

