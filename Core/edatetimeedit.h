#ifndef EDATETIMEEDIT_H
#define EDATETIMEEDIT_H

#include "core_global.h"

#include <QDateTimeEdit>

class CORE_EXPORT EDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit EDateTimeEdit(QWidget *parent = nullptr);
    explicit EDateTimeEdit(const QTime &time, QWidget *parent = nullptr);
    explicit EDateTimeEdit(const QDate &date, QWidget *parent = nullptr);
    explicit EDateTimeEdit(const QDateTime &datetime, QWidget *parent = nullptr);

    ~EDateTimeEdit();

    /**
     * @brief setEmptyEnabled
     * 设置时间显示是否允许设置为空字符串
     * @param enable
     */
    void  setEmptyEnabled(bool enable = true);

    /**
     * @brief empteEnabled
     * @return 是否被设置为能显示空字符串
     */
    bool emptyEnabled() const;

    /**
     * @brief text
     * @return 返回输入框内的文本
     */
    QString text() const;


    /**
     * @brief date
     * @return 返回日期，如果字符串为空，则返回一个invalid的QDate
     */
    QDate date() const;

    /**
     * @brief dateTime
     * @return 返回时间日期，如果字符串为空，则返回一个invalid的QDateTime
     */
    QDateTime dateTime() const;

    /**
     * @brief time
     * @return 返回时间，如果字符串为空，则返回一个invalid的QTime
     */
    QTime time() const;

    /**
     * @brief setDisplayFormat
     * 设置时间的显示格式
     * @param format
     */
    void setDisplayFormat(const QString &format);

    /**
     * @brief clearDisplayText
     * 清空显示文本
     */
    void clearDisplayText();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void paintEvent(QPaintEvent *event) override;

    virtual bool event(QEvent *event) override;

private:
    Q_DISABLE_COPY(EDateTimeEdit);
    Q_DECLARE_D(EDateTimeEdit);
    Q_DECLARE_PRIVATE(EDateTimeEdit);
};

#endif // EDATETIMEEDIT_H
