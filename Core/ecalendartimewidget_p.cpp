#include "ecalendartimewidget_p.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTime>

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
    return m_selectedDate;
}

void ECalendarTimeWidgetPrivate::setMinimumDateTime(const QDateTime &dateTime)
{
    m_minDateTime = dateTime;
    if(m_timeWidget)
    {
    }
}

void ECalendarTimeWidgetPrivate::setMaximumDateTime(const QDateTime &dateTime)
{
    m_maxDateTime = dateTime;
}

void ECalendarTimeWidgetPrivate::setDateTimeRange(const QDateTime &min,const QDateTime &max)
{
    setMinimumDateTime(min);
    setMaximumDateTime(max);
}

void ECalendarTimeWidgetPrivate::setSelectedDateTime(const QDateTime &dateTime)
{
    m_selectedDate = dateTime;
}
