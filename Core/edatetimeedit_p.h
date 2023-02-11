#ifndef EDATETIMEEDITPRIVATE_H
#define EDATETIMEEDITPRIVATE_H

#include <QObject>

class EDateTimeEdit;
class QLineEdit;

class EDateTimeEditPrivate : public QObject
{
    Q_OBJECT
    EDateTimeEdit * const q_ptr;
    Q_DISABLE_COPY(EDateTimeEditPrivate);
    Q_DECLARE_PUBLIC(EDateTimeEdit);
public:
    explicit EDateTimeEditPrivate(EDateTimeEdit *parent);

public:
    QLineEdit *lineEdit = nullptr;

    //设置时间是否可以为空
    bool m_emptyEnabled = true;
};

#endif // EDATETIMEEDITPRIVATE_H
