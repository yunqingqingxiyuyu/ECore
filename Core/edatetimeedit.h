#ifndef EDATETIMEEDIT_H
#define EDATETIMEEDIT_H

#include "core_global.h"

#include <QDateTimeEdit>

class CORE_EXPORT EDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit EDateTimeEdit(QWidget *parent = nullptr);
    ~EDateTimeEdit();
};

#endif // EDATETIMEEDIT_H
