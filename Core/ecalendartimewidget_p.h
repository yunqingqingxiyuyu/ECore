#ifndef ECALENDARTIMEWIDGETPRIVATE_H
#define ECALENDARTIMEWIDGETPRIVATE_H

#include <QObject>
#include <QDateTime>

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

    /**
     * @brief maximunDateTime
     * @return 返回的最大时间日期
     */
    QDateTime maximunDateTime() const;

    /**
     * @brief minimumDateTime
     * @return 返回最小时间范围的日期时间
     */
    QDateTime minimumDateTime() const;

    /**
     * @brief selectedDateTime
     * @return 返回所选的时间日期
     */
    QDateTime selectedDateTime() const;

    /**
     * @brief setMaximumDateTime
     * 设置可选择的最大日期时间
     * @param dateTime 最大日期时间
     */
    void setMaximumDateTime(const QDateTime &dateTime);

    /**
     * @brief setMinimumDateTime
     * 设置可选择的最小日期时间
     * @param dateTime
     */
    void setMinimumDateTime(const QDateTime &dateTime);

    /**
     * @brief setDateTimeRange
     * 设置可选的日期时间范围
     * @param min
     * @param max
     */
    void setDateTimeRange(const QDateTime &min,const QDateTime &max);

    /**
     * @brief setSelectedDateTime
     * 设置选择的日期时间
     * @param dateTime
     */
    void setSelectedDateTime(const QDateTime &dateTime);

private Q_SLOTS:
    /**
     * @brief onSelectionChanged
     * 响应日期时间发生改变
     */
    void onSelectionChanged();
private:
    QWidget* timeWidget() const;

    /**
     * @brief trySetTimeRange
     * 如果当前的日期在临界位置，那么就把当前的时间设置在规定的范围内，否则时间控件不应该限制范围
     */
    void trySetTimeRange(const QDateTime &dateTime);

public:
    ETimeWidget *m_timeWidget = nullptr;

    QPushButton *m_cleanButton = nullptr;

    QVBoxLayout *m_mainLay = nullptr;
    QHBoxLayout *m_bottomLay = nullptr;

    QWidget *m_mainWidget = nullptr;

    QDateTime m_minDateTime = QDateTime();

    QDateTime m_maxDateTime = QDateTime();

    QDateTime m_selectedDateTime = QDateTime::currentDateTime();
};

#endif // ECALENDARTIMEWIDGETPRIVATE_H
