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
     * @brief show
     * 显示showTime长时间，如果showTime设置一个小于等于0的数表示一直显示，如果设置了一个正数，表示
     * 显示showTime毫秒后，引用计数减去1，直到为0后关闭窗口
     * @param showTime:ms
     */
    void show(int showTime = -1);

    /**
     * @brief setParent
     * @param parent
     */
    void setParent(QWidget *parent);

    /**
     * @brief hide
     * 隐藏加载控件
     * @note 只有在控件的引用计数为0时才会隐藏，因此hide()应该与show()函数是配对的
     * 如果需要直接隐藏部件，可以直接调用setVisible()函数。
     */
    void hide();

    /**
     * @brief refrenceCount
     * @return 返回当前的引用计数数量
     */
    int refrenceCount() const;

    /**
     * @brief setMaxShowTime
     * 设置最长的显示时间，时间到了之后，强制清除引用计数并关闭窗口
     * @param second 单位:s
     */
    void setMaxShowTime(int ms);

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

    /**
     * @brief setScaledSize
     * 设置图标的缩放大小
     * @param size
     */
    void setScaledSize(const QSize &size);

    /**
     * @brief scaledSize
     * 返回缩放大小
     * @return
     */
    QSize scaledSize() const;

    /**
     * @brief font
     * 返回文本的font
     * @return
     */
    QFont font() const;

    /**
     * @brief setFont
     * 设置文本字体
     * @param font
     */
    void setFont(const QFont &font);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DISABLE_COPY(ELoadingWidget);
    Q_DECLARE_D(ELoadingWidget);
    Q_DECLARE_PRIVATE(ELoadingWidget);
};

#endif // ELOADINGWIDGET_H
