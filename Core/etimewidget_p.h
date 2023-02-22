#ifndef ETIMEWIDGETPRIVATE_H
#define ETIMEWIDGETPRIVATE_H

#include <QObject>
#include <QTime>
#include <QBoxLayout>

class ETimeWidget;
class QLabel;

class ETimeWidgetPrivate : public QObject
{
    Q_OBJECT
    ETimeWidget *const q_ptr;
    Q_DISABLE_COPY(ETimeWidgetPrivate);
    Q_DECLARE_PUBLIC(ETimeWidget);
public:
    explicit ETimeWidgetPrivate(const QTime &time,ETimeWidget *parent);

    /**
     * @brief createTimeWidget
     * @return 返回时间控件
     */
    QLayout* createTimeWidget();


    /**
     * @brief contains
     * @param obj
     * @return 如果包含obj对象，则返回true否则返回false,如果obj是nullptr,返回false;
     */
    bool contains(const QObject *obj);

    /**
     * @brief handleTimeWidget
     * @param obj
     * @param event
     * @return 处理时间控件事件
     */
    bool handleTimeWidget(QObject *obj, QEvent *event);
private:

    void update(const QTime &time);

public:
    QTime m_time;

private:
    QLabel *m_hour = nullptr;
    QLabel *m_minute = nullptr;
    QLabel *m_second = nullptr;

    QLabel *m_hour1 = nullptr;
    QLabel *m_minute1 = nullptr;
    QLabel *m_second1 = nullptr;

    QLabel *m_hour2 = nullptr;
    QLabel *m_minute2 = nullptr;
    QLabel *m_second2 = nullptr;


    QBoxLayout::Direction m_dir;
};

#endif // ETIMEWIDGETPRIVATE_H
