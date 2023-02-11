#include "edatetimeedit_p.h"

#include "edatetimeedit.h"

#include <QDebug>

EDateTimeEditPrivate::EDateTimeEditPrivate(EDateTimeEdit *parent):
    q_ptr(parent)
{
    Q_Q(EDateTimeEdit);
    lineEdit = q->QDateTimeEdit::lineEdit();
}
