#include "eloadingwidget_p.h"

#include "eloadingwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>

ELoadingWidgetPrivate::ELoadingWidgetPrivate(
        ELoadingWidget *parent,
        const QString &text,
        qint32 delayMillisecond,
        QWidget *topParent
        ):
    q_ptr(parent),
    m_topWidget(topParent)
{
    Q_Q(ELoadingWidget);
    q->raise();
    q->setWindowModality(Qt::WindowModal);

    m_movie = new QMovie(q);
    m_label = new QLabel(q);
    m_textLabel = new QLabel(text,q);

    m_label->setAlignment(Qt::AlignHCenter);
    m_textLabel->setAlignment(Qt::AlignCenter);


    QVBoxLayout *mainLay = new QVBoxLayout;

    mainLay->addStretch();
    mainLay->addWidget(m_label);
    mainLay->addWidget(m_textLabel);
    mainLay->addStretch();
    q->setLayout(mainLay);


    m_movie->setFileName(":/resources/loading.gif");
    m_label->setMovie(m_movie);

    if(delayMillisecond > 0)
        QTimer::singleShot(delayMillisecond, this, &ELoadingWidgetPrivate::startPlay);
}

ELoadingWidgetPrivate::~ELoadingWidgetPrivate()
{
    m_movie->stop();
}

void ELoadingWidgetPrivate::setFileName(const QString &fileName)
{
    m_movie->setFileName(fileName);
}

void ELoadingWidgetPrivate::startPlay()
{
    Q_Q(ELoadingWidget);
    QSize parentSize;
    QPoint pos(0,0);

    if(m_topWidget != nullptr)
    {
        m_topWidget->installEventFilter(q);
        parentSize = m_topWidget->size();
        pos = m_topWidget->mapToGlobal(QPoint(0,0));
    }
    else
    {
        parentSize = QApplication::desktop()->size();
    }

    q->setGeometry(QRect(pos,parentSize));

    q->setWindowFlags(q->windowFlags() |
                      Qt::FramelessWindowHint |
                      Qt::Dialog |
                      Qt::WindowStaysOnTopHint);

    q->setWindowOpacity(0.8);

    m_movie->start();
    q->QWidget::show();
    q->raise();
}

void ELoadingWidgetPrivate::setText(const QString &text)
{
    m_textLabel->setText(text);
}
