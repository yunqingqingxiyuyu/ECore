#include "edatetimeedit.h"

#include "edatetimeedit_p.h"

#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

EDateTimeEdit::EDateTimeEdit(QWidget *parent):
    QDateTimeEdit(parent),
    d_ptr(new EDateTimeEditPrivate(this))
{

}

EDateTimeEdit::EDateTimeEdit(const QTime &time, QWidget *parent):
    QDateTimeEdit(time,parent),
    d_ptr(new EDateTimeEditPrivate(this))
{

}

EDateTimeEdit::EDateTimeEdit(const QDate &date, QWidget *parent):
    QDateTimeEdit(date,parent),
    d_ptr(new EDateTimeEditPrivate(this))
{

}

EDateTimeEdit::EDateTimeEdit(const QDateTime &datetime, QWidget *parent):
    QDateTimeEdit(datetime,parent),
    d_ptr(new EDateTimeEditPrivate(this))
{

}

EDateTimeEdit::~EDateTimeEdit()
{

}

void EDateTimeEdit::setEmptyEnabled(bool enable)
{
    Q_D(EDateTimeEdit);
    d->m_emptyEnabled = enable;
}

bool EDateTimeEdit::emptyEnabled() const
{
    Q_D(const EDateTimeEdit);
    return d->m_emptyEnabled;
}

QString EDateTimeEdit::text() const
{
    Q_D(const EDateTimeEdit);
    if(emptyEnabled() && d->lineEdit->text().isEmpty())
    {
        return	QString();
    }

    return QDateTimeEdit::text();
}

void EDateTimeEdit::keyPressEvent(QKeyEvent *event)
{
    Q_D(EDateTimeEdit);
    switch (static_cast<qint64>(event->key())) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Backspace:
        if(emptyEnabled() && d->lineEdit->selectedText() == d->lineEdit->text())
        {
            d->lineEdit->clear();
            d->lineEdit->setText("");
            return;
        }
    }

    return QDateTimeEdit::keyPressEvent(event);
}

void EDateTimeEdit::focusInEvent(QFocusEvent *event)
{
    Q_D(EDateTimeEdit);
    QString temp = d->lineEdit->text();
    if(emptyEnabled())
    {
        d->lineEdit->setText(temp);
    }
    else
    {
        QDateTimeEdit::focusInEvent(event);
    }
}

void EDateTimeEdit::focusOutEvent(QFocusEvent *event)
{
    Q_D(EDateTimeEdit);
    QString temp = d->lineEdit->text();
    QDateTimeEdit::focusOutEvent(event);
    if(emptyEnabled())
    {
        d->lineEdit->setText(temp);
    }
}

void EDateTimeEdit::paintEvent(QPaintEvent *event)
{
    QDateTimeEdit::paintEvent(event);
}

QDate EDateTimeEdit::date() const
{
    Q_D(const EDateTimeEdit);

    if(emptyEnabled() && d->lineEdit->text().isEmpty())
    {
        return QDate();
    }

    return QDateTimeEdit::date();
}

QDateTime EDateTimeEdit::dateTime() const
{
    Q_D(const EDateTimeEdit);

    if(emptyEnabled() && d->lineEdit->text().isEmpty())
    {
        return QDateTime();
    }

    return QDateTimeEdit::dateTime();
}

QTime EDateTimeEdit::time() const
{
    Q_D(const EDateTimeEdit);

    if(emptyEnabled() && d->lineEdit->text().isEmpty())
    {
        return QTime();
    }

    return QDateTimeEdit::time();
}

void EDateTimeEdit::setDisplayFormat(const QString &format)
{
    Q_D(EDateTimeEdit);

    QString temp = d->lineEdit->text();

    QDateTimeEdit::setDisplayFormat(format);

    if(emptyEnabled() && temp.isEmpty())
    {
        d->lineEdit->setText(temp);
    }
}

void EDateTimeEdit::clearDisplayText()
{
    Q_D(EDateTimeEdit);
    if(emptyEnabled())
    {
        d->lineEdit->setText("");
    }
}

void EDateTimeEdit::showEvent(QShowEvent *event)
{
    Q_D(EDateTimeEdit);
    QString temp = d->lineEdit->text();
    qDebug() << temp;

    QDateTimeEdit::showEvent(event);

    if(emptyEnabled())
    {
        d->lineEdit->setText(temp);
    }
}
