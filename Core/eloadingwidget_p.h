#ifndef ELOADINGWIDGETPRIVATE_H
#define ELOADINGWIDGETPRIVATE_H

#include <QObject>

class ELoadingWidget;
class QMovie;
class QLabel;


class ELoadingWidgetPrivate : public QObject
{
    Q_OBJECT
    ELoadingWidget * const q_ptr;
    Q_DISABLE_COPY(ELoadingWidgetPrivate);
    Q_DECLARE_PUBLIC(ELoadingWidget);
public:
    explicit ELoadingWidgetPrivate(ELoadingWidget *parent,const QString &text = "",qint32 delayMillisecond = 0);
    virtual ~ELoadingWidgetPrivate() override;

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
};

#endif // ELOADINGWIDGETPRIVATE_H
