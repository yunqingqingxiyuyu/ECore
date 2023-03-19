#ifndef EDATETIMEEDITPRIVATE_H
#define EDATETIMEEDITPRIVATE_H

#include <QObject>
#include <QDateTime>

class EDateTimeEdit;
class QLineEdit;
class ECalendarTimeWidget;

class EDateTimeEditPrivate : public QObject
{
    Q_OBJECT
    EDateTimeEdit * const q_ptr;
    Q_DISABLE_COPY(EDateTimeEditPrivate);
    Q_DECLARE_PUBLIC(EDateTimeEdit);
public:
    explicit EDateTimeEditPrivate(EDateTimeEdit *parent);

public:

    /**
     * @brief maximunDateTime
     * @return 返回的最大时间日期
     */
    QDateTime maximunDateTime() const {return m_minDateTime;}

    /**
     * @brief minimumDateTime
     * @return 返回最小时间范围的日期时间
     */
    QDateTime minimumDateTime() const{return m_maxDateTime;}

    /**
     * @brief selectedDateTime
     * @return 返回所选的时间日期
     */
    QDateTime selectedDateTime() const{return  m_selectedDate;}

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
     * @brief setSelectedDateTime
     * 设置选择的日期时间
     * @param dateTime
     */
    void setSelectedDateTime(const QDateTime &dateTime);

    /**
     * @brief setCalendarTimeWidget
     * 设置弹出的日历时间对话框，编辑器不获取日历时间控件的所有权
     * @param calendarTimeWidget
     */
    void setCalendarTimeWidget(ECalendarTimeWidget *calendarTimeWidget);

    /**
     * @brief calendarTimeWidget
     * @return 返回日期时间日历控件
     */
    ECalendarTimeWidget* calendarTimeWidget() const{return m_calendarTimeWidget;}

private:
    QLineEdit *lineEdit = nullptr;

    //设置时间是否可以为空
    bool m_emptyEnabled = true;

    QDateTime m_minDateTime = QDateTime();

    QDateTime m_maxDateTime = QDateTime();

    QDateTime m_selectedDate = QDateTime();

    ECalendarTimeWidget *m_calendarTimeWidget = nullptr;
};

#endif // EDATETIMEEDITPRIVATE_H
