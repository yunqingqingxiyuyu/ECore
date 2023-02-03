#include "elineedit.h"

#include <qglobal.h>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionFrame>

#include "elineedit_p.h"

ELineEdit::ELineEdit(const QString &contents, QWidget *parent):
    QLineEdit(contents.trimmed(),parent),
    d_ptr(new ELineEditPrivate(this))

{
    Q_D(ELineEdit);
    d->init();
}

ELineEdit::ELineEdit(QWidget *parent):
    ELineEdit(QString(),parent)
{
}

ELineEdit::~ELineEdit()
{
    Q_D(ELineEdit);
    d->deleteLater();
}

void ELineEdit::setDecoration(bool enabled)
{
    Q_D(ELineEdit);
    d->setDecoration(enabled);
}

bool ELineEdit::isDecoration() const
{
    Q_D(const ELineEdit);
    return d->isDecoration();
}

void ELineEdit::setText(const QString &text)
{
    if(isDecoration())
    {
        QLineEdit::setText(text.trimmed());
    }
    else
    {
        QLineEdit::setText(text);
    }
}

QString ELineEdit::text() const
{
    if(isDecoration())
    {
        return QLineEdit::text().trimmed();
    }

    return QLineEdit::text();
}

void ELineEdit::setClearButtonEnabled(bool enabled)
{
    Q_D(ELineEdit);
    d->setClearButtonEnabled(enabled);
}

bool ELineEdit::isClearButtonEnabled() const
{
    Q_D(const ELineEdit);
    return d->isClearButtonEnabled();
}

void ELineEdit::setSearchButtonEnabled(bool enabled)
{
    Q_D(ELineEdit);
    d->setSearchButtonEnabled(enabled);
}

bool ELineEdit::isSearchButtonEnabled() const
{
    Q_D(const ELineEdit);
    return d->isSearchButtonEnabled();
}

