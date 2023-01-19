#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include "core_global.h"

#include <QLineEdit>

class ELineEditPrivate;

/**
 * @brief The ELineEdit class
 * @details 扩展QLineEdit,用于获取设置文本时，自动对文本做一些处理工作
 */
class CORE_EXPORT ELineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ELineEdit(const QString &contents, QWidget *parent = nullptr);
    explicit ELineEdit(QWidget *parent = nullptr);
    virtual ~ELineEdit();

    /**
     * @brief setDecoration
     * @param enable
     * @details 设置文本设置是否有效，有效后读写的文本都会自动去除前后空白字符,默认开启
     */
    void setDecoration(bool enable = true);
    /**
     * @brief isDecoration
     * @return 返回是否显示修饰后的文本。
     */
    bool isDecoration() const;

    /**
     * @brief setText
     * @param text 设置的文本
     * @details 将text去除前后空格后填入
     */
    void setText(const QString &text);

    /**
     * @brief text
     * @return 返回文本，文本的前后空格被清除
     */
    QString text() const;

    /**
     * @brief setClearButtonEnabled
     * @param enable
     * @details 设置清除按钮是否显示，默认显示
     */
    void setClearButtonEnabled(bool enable);

    /**
     * @brief isClearButtonEnabled
     * @return 返回清除按钮是否应该显示
     */
    bool isClearButtonEnabled() const;

    /**
     * @brief setSearchButtonEnabled
     * @param enable
     * @details 设置查找按钮是否应该显示,默认查找按钮显示
     */
    void setSearchButtonEnabled(bool enable);

    /**
     * @brief isSearchButtonEnabled
     * @return 设置查找按钮是否应该显示，默认显示
     */
    bool isSearchButtonEnabled() const;

signals:
    /**
     * @brief searchPressed
     * @param text 需要查找的文本
     * @details 当点击回车或者点击查询按钮时，触发本信号。
     */
    void searchPressed(const QString &text);

    /**
     * @brief textChanged
     * @param text 去除前后空白字符的文本内容
     */
    void textChanged(const QString &text);

    /**
     * @brief textEdited
     * @param text 去除前后空白字符的文本内容
     */
    void textEdited(const QString &text);

private slots:
    /**
     * @brief searchButtonPressed
     * @details 响应查询按钮按下
     */
    void searchButtonPressed();

private:
    Q_DISABLE_COPY(ELineEdit);
    ELineEditPrivate *d_ptr = nullptr;
    Q_DECLARE_PRIVATE(ELineEdit);
};

#endif // ELINEEDIT_H
