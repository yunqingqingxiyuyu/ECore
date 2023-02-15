#ifndef ETIMEWIDGETPRIVATE_H
#define ETIMEWIDGETPRIVATE_H

#include <QObject>
#include <QTime>

class ETimeWidget;

class ETimeWidgetPrivate : public QObject
{
    Q_OBJECT
    ETimeWidget *const q_ptr;
    Q_DISABLE_COPY(ETimeWidgetPrivate);
    Q_DECLARE_PUBLIC(ETimeWidget);
public:
    explicit ETimeWidgetPrivate(const QTime &time,ETimeWidget *parent);

private:
//    QWidget* createTimeWidget();

public:
    QTime m_time;
};

#endif // ETIMEWIDGETPRIVATE_H
