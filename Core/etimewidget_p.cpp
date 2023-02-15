#include "etimewidget_p.h"

#include "etimewidget.h"

ETimeWidgetPrivate::ETimeWidgetPrivate(const QTime &time,ETimeWidget *parent):
    q_ptr(parent),
    m_time(time)
{
}
