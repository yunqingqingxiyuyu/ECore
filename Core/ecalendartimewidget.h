#ifndef ECALENDARTIMEWIDGET_H
#define ECALENDARTIMEWIDGET_H

#include "core_global.h"

#include <QCalendarWidget>

class QPushButton;

class CORE_EXPORT ECalendarTimeWidget : public QCalendarWidget
{
    Q_OBJECT

public:
    explicit ECalendarTimeWidget(QWidget *parent = nullptr);
    virtual ~ECalendarTimeWidget();

    QSize sizeHint() const override;

    void setDateTime(const QDateTime &dateTime);

    QDateTime dateTime() const;

    QTime time() const;

    /**
     * @brief setCleanButton
     * 设置的button的所有权归类对象所有，会在必要时释放，因此请不要再栈上创建button对象。
     * 如果button为nullptr,则按钮被释放不显示。
     * @param button
     */
    void setCleanButton(QPushButton *button);

    /**
     * @brief setCleanButtonText
     * 设置清空按钮显示文本
     * @param text
     */
    void setCleanButtonText(const QString &text);

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


public Q_SLOTS:

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

Q_SIGNALS:
    /**
     * @brief cleanButtonClicked
     * 清空按钮触发
     */
    void cleanButtonClicked();

private:
    Q_DISABLE_COPY(ECalendarTimeWidget);
    Q_DECLARE_D(ECalendarTimeWidget);
    Q_DECLARE_PRIVATE(ECalendarTimeWidget);
};

#endif // ECALENDARTIMEWIDGET_H
