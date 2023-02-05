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
        qint32 delayMillisecond
        ):
    q_ptr(parent)
{
    Q_Q(ELoadingWidget);
    q->raise();

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

    q->setWindowOpacity(0);

    QSize parentSize;

    if(parent != nullptr)
    {
        parent->installEventFilter(this);
        parentSize = parent->size();
    }
    else
    {
        parentSize = QApplication::desktop()->size();
    }

    q->resize(parentSize);

    q->setWindowFlags(q->windowFlags() | Qt::FramelessWindowHint | Qt::WindowTransparentForInput |  Qt::WindowStaysOnTopHint);

    m_movie->setFileName(":/resources/loading.gif");
    m_label->setMovie(m_movie);

    QTimer::singleShot(delayMillisecond, this, &ELoadingWidgetPrivate::startPlay);
}

ELoadingWidgetPrivate::~ELoadingWidgetPrivate()
{
    m_movie->stop();
    delete m_movie;
    m_movie = nullptr;
}

void ELoadingWidgetPrivate::setFileName(const QString &fileName)
{
    m_movie->setFileName(fileName);
}

void ELoadingWidgetPrivate::startPlay()
{
    Q_Q(ELoadingWidget);
    m_movie->start();
    q->show();
}

void ELoadingWidgetPrivate::setText(const QString &text)
{
    m_textLabel->setText(text);
}
