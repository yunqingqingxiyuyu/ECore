#ifndef ETIMEWIDGET_H
#define ETIMEWIDGET_H

#include "core_global.h"

#include <QWidget>

class CORE_EXPORT ETimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ETimeWidget(const QTime &time,QWidget *parent = nullptr);
    ~ETimeWidget();


    /**
     * @brief time
     * @return 返回当前时间
     */
    QTime time() const;

    /**
     * @brief setTime
     * 设置控件当前时间
     * @param time
     */
    void setTime(const QTime &time);

signals:

    /**
     * @brief timeChanged
     * 时间有变化
     * @param time
     */
    void timeChanged(const QTime &time);

    /**
     * @brief clicked
     * 点击了时间
     * @param time当前事件
     */
    void clicked(const QTime &time);

protected:
    /**
     * @brief createTimeWidget
     * 返回时间控件界面
     */
    virtual QLayout* createTimeWidget();

    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    Q_DISABLE_COPY(ETimeWidget);
    Q_DECLARE_D(ETimeWidget);
    Q_DECLARE_PRIVATE(ETimeWidget);
};

#endif // ETIMEWIDGET_H
