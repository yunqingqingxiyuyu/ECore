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
    if(parent() == watched)
    {
        if(event->type() == QEvent::Resize)
        {
            QWidget *parent = static_cast<QWidget *>(watched);
            if(parent != nullptr)
            {
                resize(parent->size());
                update();
            }
        }
        return false;
    }

    return QWidget::eventFilter(watched,event);
}
