#include "eloadingwidget.h"

#include "eloadingwidget_p.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>

ELoadingWidget::ELoadingWidget(
        const QString &text,
        qint32 delayMillisecond,
        QWidget *parent
        ):
    QWidget(parent),
    d_ptr(new ELoadingWidgetPrivate(this,text,delayMillisecond,parent))
{
}

ELoadingWidget::ELoadingWidget(QWidget *parent) :
    ELoadingWidget(QString(),0,parent)
{

}

ELoadingWidget::~ELoadingWidget()
{
    delete d_ptr;
    d_ptr = nullptr;
}

void ELoadingWidget::show(int showTime)
{
    Q_D(ELoadingWidget);
    ++(d->m_refrenceCount);

    if(!isVisible())
    {
        d->startPlay();
    }

    if(showTime > 0)
    {
        QTimer::singleShot(showTime,this,[&](){
            hide();
        });
    }
}

void ELoadingWidget::setParent(QWidget *parent)
{
    Q_D(ELoadingWidget);
    QWidget::setParent(parent);
    d->m_topWidget = parent;
}

void ELoadingWidget::hide()
{
    Q_D(ELoadingWidget);
    --(d->m_refrenceCount);
    d->m_refrenceCount = d->m_refrenceCount < 0 ? 0 : d->m_refrenceCount;

    if(d->m_refrenceCount <= 0)
    {
        QWidget::hide();
    }
}

int ELoadingWidget::refrenceCount() const
{
    Q_D(const ELoadingWidget);
    return d->m_refrenceCount;
}

void ELoadingWidget::setMaxShowTime(int ms)
{
    QTimer::singleShot(ms,this,[&](){
        Q_D(ELoadingWidget);
        d->m_refrenceCount = 0;
        hide();
    });
}

void ELoadingWidget::setFileName(const QString &fileName)
{
    Q_D(ELoadingWidget);
    d->setFileName(fileName);
}

void ELoadingWidget::setText(const QString &text)
{
    Q_D(ELoadingWidget);
    d->setText(text);
}

bool ELoadingWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(ELoadingWidget);

    if(event->type() == QEvent::Move)
    {
        QPoint pos = d->m_topWidget->mapToGlobal(QPoint(0,0));
        this->move(pos);
    }

    if(d->m_topWidget == watched)
    {
        switch (static_cast<int>(event->type())) {
        case QEvent::Resize:
        {
            QWidget *parent = static_cast<QWidget *>(watched);
            if(parent != nullptr)
            {
                resize(parent->size());
                update();
            }
            break;
        }
        }
        return false;
    }


    return QWidget::eventFilter(watched,event);
}

void ELoadingWidget::setScaledSize(const QSize &size)
{
    Q_D(ELoadingWidget);
    d->m_movie->setScaledSize(size);
}

QSize ELoadingWidget::scaledSize() const
{
    Q_D(const ELoadingWidget);
    return d->m_movie->scaledSize();
}

QFont ELoadingWidget::font() const
{
    Q_D(const ELoadingWidget);
    return d->m_textLabel->font();
}

void ELoadingWidget::setFont(const QFont &font)
{
    Q_D(ELoadingWidget);
    d->m_textLabel->setFont(font);
}
