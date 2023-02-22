#include "etimewidget_p.h"

#include "etimewidget.h"

#include <QLabel>
#include <QWheelEvent>

#include <QDebug>

static int hour = 60 * 60 * 1;
static int minute = 60 * 1;
static int second = 1;

ETimeWidgetPrivate::ETimeWidgetPrivate(const QTime &time,ETimeWidget *parent) :
    q_ptr(parent),
    m_time(time)
{

}

QLayout* ETimeWidgetPrivate::createTimeWidget()
{
    Q_Q(ETimeWidget);

    QGridLayout *layout = new QGridLayout;

    m_hour = new QLabel("0",q);
    m_minute = new QLabel("0",q);
    m_second = new QLabel("0",q);

    m_hour1 = new QLabel("0",q);
    m_minute1 = new QLabel("0",q);
    m_second1 = new QLabel("0",q);

    m_hour2 = new QLabel("0",q);
    m_minute2 = new QLabel("0",q);
    m_second2 = new QLabel("0",q);

    m_minute->setObjectName("ETimeWidget_minute");

    m_hour->setAlignment(Qt::AlignCenter);
    m_minute->setAlignment(Qt::AlignCenter);
    m_second->setAlignment(Qt::AlignCenter);

    m_hour1->setAlignment(Qt::AlignCenter);
    m_minute1->setAlignment(Qt::AlignCenter);
    m_second1->setAlignment(Qt::AlignCenter);

    m_hour2->setAlignment(Qt::AlignCenter);
    m_minute2->setAlignment(Qt::AlignCenter);
    m_second2->setAlignment(Qt::AlignCenter);

    m_hour->installEventFilter(q);
    m_minute->installEventFilter(q);
    m_second->installEventFilter(q);

    QFont font = q->font();
    font.setBold(true);
    font.setPixelSize(20);
    m_hour->setFont(font);
    m_minute->setFont(font);
    m_second->setFont(font);


    font.setPixelSize(16);
    m_hour1->setFont(font);
    m_minute1->setFont(font);
    m_second1->setFont(font);

    m_hour2->setFont(font);
    m_minute2->setFont(font);
    m_second2->setFont(font);

    QFrame *fram1 = new QFrame;
    fram1->setFrameShape(QFrame::HLine);
    fram1->setLineWidth(2);
    QFrame *fram2 = new QFrame;
    fram2->setFrameShape(QFrame::HLine);
    fram2->setLineWidth(2);

    layout->addWidget(m_hour1,0,0);
    layout->addWidget(m_minute1,0,1);
    layout->addWidget(m_second1,0,2);

    layout->addWidget(fram1,1,0,1,3);

    layout->addWidget(m_hour,2,0);
    layout->addWidget(m_minute,2,1);
    layout->addWidget(m_second,2,2);

    layout->addWidget(fram2,3,0,1,3);

    layout->addWidget(m_hour2,4,0);
    layout->addWidget(m_minute2,4,1);
    layout->addWidget(m_second2,4,2);

    layout->setSpacing(0);

    if(!m_time.isValid())
    {
        m_time.setHMS(0,0,0);
    }

    update(m_time);

    return layout;
}

bool ETimeWidgetPrivate::contains(const QObject *obj)
{
    if(!obj)
        return false;

    if(obj == m_hour || obj == m_minute || obj == m_second)
        return true;

    return false;
}

bool ETimeWidgetPrivate::handleTimeWidget(QObject *obj, QEvent *event)
{
    //检测鼠标滚轮事件
    if(event->type() == QEvent::Wheel)
    {
        Q_Q(ETimeWidget);
        QWheelEvent *wheel = static_cast<QWheelEvent *>(event);

        auto angle = wheel->angleDelta();

        int increment = 1;

        if(angle.ry() > 0)
        {
            increment = -1;
        }
        else
        {
            increment = 1;
        }

        if(obj == m_hour)
        {
           m_time = m_time.addSecs(60 * 60 * increment);
        }
        else if(obj == m_minute)
        {
           m_time = m_time.addSecs(60 * increment);
        }
        else
        {
            m_time = m_time.addSecs(increment);
        }

        update(m_time);

        emit q->timeChanged(m_time);

        return true;
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        //鼠标单击——一般表示选择
        Q_Q(ETimeWidget);
        QMouseEvent *mouse = static_cast<QMouseEvent *>(event);

        if(mouse->buttons() & Qt::LeftButton)
        {
            emit q->clicked(m_time);
            return true;
        }

        return false;
    }
    return false;
}

void ETimeWidgetPrivate::update(const QTime &time)
{
    m_hour->setNum(time.hour());
    m_minute->setNum(time.minute());
    m_second->setNum(time.second());

    m_hour1->setNum(time.addSecs(hour * -1).hour());
    m_minute1->setNum(time.addSecs(minute * -1).minute());
    m_second1->setNum(time.addSecs(second * -1).second());

    m_hour2->setNum(time.addSecs(hour * 1).hour());
    m_minute2->setNum(time.addSecs(minute * 1).minute());
    m_second2->setNum(time.addSecs(second * 1).second());
}
