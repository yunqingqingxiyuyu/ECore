#include "ecalendartimewidget.h"
#include "ecalendartimewidget_p.h"
#include "ETimeWidget"

#include <QLayout>

ECalendarTimeWidget::ECalendarTimeWidget(QWidget *parent) :
    QCalendarWidget(parent),
    d_ptr(new ECalendarTimeWidgetPrivate(this))
{
    Q_D(ECalendarTimeWidget);
    QCalendarWidget::layout()->addWidget(d->timeWidget());

    setLayout(QCalendarWidget::layout());
}

ECalendarTimeWidget::~ECalendarTimeWidget()
{

}

QSize ECalendarTimeWidget::sizeHint() const
{
    Q_D(const ECalendarTimeWidget);
    auto size = QCalendarWidget::sizeHint();
    size.setHeight(size.height() + d->timeWidget()->sizeHint().height());
    return size;
}


void ECalendarTimeWidget::setDateTime(const QDateTime &dateTime)
{
    Q_D(ECalendarTimeWidget);
    QCalendarWidget::setSelectedDate(dateTime.date());
    d->setDateTime(dateTime);
}

QDateTime ECalendarTimeWidget::dateTime() const
{
    Q_D(const ECalendarTimeWidget);
    QDate date = QCalendarWidget::selectedDate();
    QTime time = d->time();

    return QDateTime(date,time);
}

QTime ECalendarTimeWidget::time() const
{
    Q_D(const ECalendarTimeWidget);
    return d->time();
}
