#ifndef ECALENDARTIMEWIDGETPRIVATE_H
#define ECALENDARTIMEWIDGETPRIVATE_H

#include <QObject>

class ECalendarTimeWidget;
class ETimeWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;

class ECalendarTimeWidgetPrivate : public QObject
{
    Q_OBJECT
    ECalendarTimeWidget *const q_ptr;
    Q_DISABLE_COPY(ECalendarTimeWidgetPrivate);
    Q_DECLARE_PUBLIC(ECalendarTimeWidget);

public:
    explicit ECalendarTimeWidgetPrivate(ECalendarTimeWidget *parent);

    /**
     * @brief setDateTime
     * 设置日期时间
     * @param dateTime
     */
    void setDateTime(const QDateTime &dateTime);

    /**
     * @brief time
     * @return 返回时间
     */
    QTime time() const;

    /**
     * @brief setCleanButton
     * 设置清空按钮
     * @param button
     */
    void setCleanButton(QPushButton *button);

    /**
     * @brief setCleanButtonText
     * 设置清空按钮显示文本
     * @param button
     */
    void setCleanButtonText(const QString &text);

    /**
     * @brief sizeHint
     * @return 返回恰当的大小
     */
    QSize sizeHint() const;
private:
    QWidget* timeWidget() const;

public:
    ETimeWidget *m_timeWidget = nullptr;

    QPushButton *m_cleanButton = nullptr;

    QVBoxLayout *m_mainLay = nullptr;
    QHBoxLayout *m_bottomLay = nullptr;

    QWidget *m_mainWidget = nullptr;
};

#endif // ECALENDARTIMEWIDGETPRIVATE_H
