#ifndef ELOADINGWIDGET_H
#define ELOADINGWIDGET_H

#include "core_global.h"
#include <QWidget>

class QMovie;
class QLabel;

/**
 * @brief The ELoadingWidget class
 * @details 显示加载图标
 */
class CORE_EXPORT ELoadingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ELoadingWidget(QWidget *parent,const QString &text,qint32 delayMillisecond = 0);
    ~ELoadingWidget();

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

private slots:
    /**
     * @brief startPlay
     * 开始播放
     */
    void startPlay();

private:
    QMovie *m_movie = nullptr;
    QLabel *m_label = nullptr;
    QLabel *m_textLabel = nullptr;
    Q_DECLARE_D(ELoadingWidget);
};

#endif // ELOADINGWIDGET_H
