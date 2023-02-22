#include "etimewidget.h"

#include "etimewidget_p.h"

ETimeWidget::ETimeWidget(const QTime &time,QWidget *parent):
    QWidget(parent),
    d_ptr(new ETimeWidgetPrivate(time,this))
{
    setLayout(createTimeWidget());
}

ETimeWidget::~ETimeWidget()
{

}

QLayout* ETimeWidget::createTimeWidget()
{
    Q_D(ETimeWidget);

    return d->createTimeWidget();
}

QTime ETimeWidget::time() const
{
    Q_D(const ETimeWidget);

    return d->m_time;
}

void ETimeWidget::setTime(const QTime &time)
{
    Q_D(ETimeWidget);

    d->m_time = time;
    d->update(d->m_time);
}

bool ETimeWidget::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(ETimeWidget);

    if(d->contains(obj))
    {
        return d->handleTimeWidget(obj,event);
    }
    else
    {
        return QWidget::eventFilter(obj,event);
    }

}
