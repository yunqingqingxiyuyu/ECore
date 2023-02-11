#ifndef ELOADINGWIDGET_H
#define ELOADINGWIDGET_H

#include "core_global.h"
#include <QWidget>

/**
 * @brief The ELoadingWidget class
 * @details 显示加载图标
 */
class CORE_EXPORT ELoadingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ELoadingWidget(const QString &text ,qint32 delayMillisecond ,QWidget *parent = nullptr);
    explicit ELoadingWidget(QWidget *parent = nullptr);
    virtual ~ELoadingWidget() override;

    /**
     * @brief setFileName
     * @details 设置显示的加载图标名
     */
    void setFileName(const QString &fileName);

    /**
     * @brief setText
     * @param text 设置要显示的文本
     */
    void setText(const QString &text);


protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DISABLE_COPY(ELoadingWidget);
    Q_DECLARE_D(ELoadingWidget);
    Q_DECLARE_PRIVATE(ELoadingWidget);
};

#endif // ELOADINGWIDGET_H
