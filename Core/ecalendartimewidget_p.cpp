#include "ecalendartimewidget_p.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTime>
#include <QDebug>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "etimewidget.h"
#include "ecalendartimewidget.h"

ECalendarTimeWidgetPrivate::ECalendarTimeWidgetPrivate(ECalendarTimeWidget *parent):
    q_ptr(parent)
{
    Q_Q(ECalendarTimeWidget);
    m_mainWidget = new QWidget;
    m_timeWidget = new ETimeWidget(QTime::currentTime());
    m_cleanButton = new QPushButton(tr("清空"));

    m_bottomLay = new QHBoxLayout;
    m_bottomLay->addStretch();
    m_bottomLay->addWidget(m_cleanButton);

    m_mainLay = new QVBoxLayout;

    m_mainLay->addWidget(m_timeWidget);
    m_mainLay->addLayout(m_bottomLay);

    m_mainWidget->setLayout(m_mainLay);

    connect(m_cleanButton,&QPushButton::clicked,q,&ECalendarTimeWidget::cleanButtonClicked);

    connect(q,&QCalendarWidget::selectionChanged,this,&ECalendarTimeWidgetPrivate::onSelectionChanged);
}

QWidget* ECalendarTimeWidgetPrivate::timeWidget() const
{
    return m_mainWidget;
}

void ECalendarTimeWidgetPrivate::setDateTime(const QDateTime &dateTime)
{
    m_timeWidget->setTime(dateTime.time());
}

QTime ECalendarTimeWidgetPrivate::time() const
{
    return m_timeWidget->time();
}

void ECalendarTimeWidgetPrivate::setCleanButton(QPushButton *button)
{
    Q_Q(ECalendarTimeWidget);
    m_bottomLay->removeWidget(m_cleanButton);
    if(m_cleanButton)
    {
        m_cleanButton->deleteLater();
    }

    m_cleanButton = button;
    if(m_cleanButton)
    {
        m_bottomLay->insertWidget(1,m_cleanButton);
        connect(m_cleanButton,&QPushButton::clicked,q,&ECalendarTimeWidget::cleanButtonClicked);
    }
}

void ECalendarTimeWidgetPrivate::setCleanButtonText(const QString &text)
{
    if(m_cleanButton)
    {
        m_cleanButton->setText(text);
    }
}

QSize ECalendarTimeWidgetPrivate::sizeHint() const
{
    return m_mainWidget->sizeHint();
}

QDateTime ECalendarTimeWidgetPrivate::minimumDateTime() const
{
    return m_minDateTime;
}

QDateTime ECalendarTimeWidgetPrivate::maximunDateTime() const
{
    return m_maxDateTime;
}

QDateTime ECalendarTimeWidgetPrivate::selectedDateTime() const
{
    return m_selectedDateTime;
}

void ECalendarTimeWidgetPrivate::setMinimumDateTime(const QDateTime &dateTime)
{
    Q_Q(ECalendarTimeWidget);
    q->QCalendarWidget::setMinimumDate(dateTime.date());
    onSelectionChanged();
    m_minDateTime = dateTime;
}

void ECalendarTimeWidgetPrivate::setMaximumDateTime(const QDateTime &dateTime)
{
    Q_Q(ECalendarTimeWidget);
    q->QCalendarWidget::setMaximumDate(dateTime.date());
    onSelectionChanged();
    m_maxDateTime = dateTime;
}

void ECalendarTimeWidgetPrivate::setDateTimeRange(const QDateTime &min,const QDateTime &max)
{
    setMinimumDateTime(min);
    setMaximumDateTime(max);
}

void ECalendarTimeWidgetPrivate::setSelectedDateTime(const QDateTime &dateTime)
{
    Q_Q(ECalendarTimeWidget);
    q->QCalendarWidget::setSelectedDate(dateTime.date());
    m_timeWidget->setTime(dateTime.time());
    m_selectedDateTime = dateTime;
}

void ECalendarTimeWidgetPrivate::onSelectionChanged()
{
    Q_Q(ECalendarTimeWidget);
    QDateTime dateTime(q->QCalendarWidget::selectedDate(),m_timeWidget->time());
    trySetTimeRange(dateTime);
}

void ECalendarTimeWidgetPrivate::trySetTimeRange(const QDateTime &dateTime)
{
    Q_Q(ECalendarTimeWidget);
    //只有在最小最大日期的时候才允许设置日期控件的时间范围，否则在正常的日期内没法设置时间
    if(minimumDateTime().isValid() && (minimumDateTime().date() >= dateTime.date()))
    {
        m_timeWidget->setMinimumTime(m_minDateTime.time());
    }
    else
    {
        m_timeWidget->setMinimumTime(QTime());
    }

    if(maximunDateTime().isValid() && (maximunDateTime().date() <= dateTime.date()))
    {
        m_timeWidget->setMaximumTime(m_maxDateTime.time());
    }
    else
    {
        m_timeWidget->setMaximumTime(QTime());
    }

    if(dateTime == m_selectedDateTime)
    {
        return ;
    }

    m_selectedDateTime = dateTime;

    emit q->selectionDateTimeChanged();
}
