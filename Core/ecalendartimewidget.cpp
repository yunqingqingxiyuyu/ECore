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

void ECalendarTimeWidget::setCleanButton(QPushButton *button)
{
    Q_D(ECalendarTimeWidget);
    d->setCleanButton(button);
}

void ECalendarTimeWidget::setCleanButtonText(const QString &text)
{
    Q_D(ECalendarTimeWidget);
    d->setCleanButtonText(text);
}

QDateTime ECalendarTimeWidget::maximunDateTime() const
{
    Q_D(const ECalendarTimeWidget);
    return d->maximunDateTime();
}

QDateTime ECalendarTimeWidget::minimumDateTime() const
{
    Q_D(const ECalendarTimeWidget);
    return d->minimumDateTime();
}

void ECalendarTimeWidget::setMaximumDateTime(const QDateTime &dateTime)
{
    Q_D(ECalendarTimeWidget);
    d->setMaximumDateTime(dateTime);
}

void ECalendarTimeWidget::setMinimumDateTime(const QDateTime &dateTime)
{
    Q_D(ECalendarTimeWidget);
    d->setMinimumDateTime(dateTime);
}

void ECalendarTimeWidget::setDateTimeRange(const QDateTime &min,const QDateTime &max)
{
    Q_D(ECalendarTimeWidget);
    d->setDateTimeRange(min,max);
}

void ECalendarTimeWidget::setSelectedDateTime(const QDateTime &dateTime)
{
    Q_D(ECalendarTimeWidget);
    d->setSelectedDateTime(dateTime);
}
