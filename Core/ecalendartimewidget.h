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
