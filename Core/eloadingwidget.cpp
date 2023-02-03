#include "eloadingwidget.h"

#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>

ELoadingWidget::ELoadingWidget(QWidget *parent,const QString &text,qint32 delayMillisecond):
    QWidget(parent)
{
    this->raise();

    m_movie = new QMovie(this);
    m_label = new QLabel(this);
    m_textLabel = new QLabel(text,this);

    setWindowOpacity(0.8);

    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->addWidget(m_label);
    mainLay->addWidget(m_textLabel);
    setLayout(mainLay);

    m_label->setMovie(m_movie);

    QTimer::singleShot(delayMillisecond, this, &ELoadingWidget::startPlay);
}

ELoadingWidget::~ELoadingWidget()
{

}

void ELoadingWidget::setFileName(const QString &fileName)
{
    m_movie->setFileName(fileName);
}

void ELoadingWidget::startPlay()
{

    m_movie->start();
}

void ELoadingWidget::setText(const QString &text)
{
    m_textLabel->setText(text);
}
