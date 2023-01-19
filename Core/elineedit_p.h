#ifndef ELINEEDITPRIVATE_H
#define ELINEEDITPRIVATE_H

#include <QObject>

class ELineEdit;
class QAction;

/**
 * @brief The ELineEditPrivate class
 */
class ELineEditPrivate : public QObject
{
    Q_OBJECT
    ELineEdit * const q_ptr;
    Q_DISABLE_COPY(ELineEditPrivate);
    Q_DECLARE_PUBLIC(ELineEdit);
public:
    explicit ELineEditPrivate(ELineEdit *parent);

    void setDecoration(bool enable = true);
    bool isDecoration() const;
    void setClearButtonEnabled(bool enable);
    bool isClearButtonEnabled() const;
    void setSearchButtonEnabled(bool enable);
    bool isSearchButtonEnabled() const;

private:
    void init();

private:
    /**
     * @brief m_isDecoration
     * @details 是否修饰文本，当有效时，从ELineEdit读写的文本都会自动去除其前后的空格
     */
    bool m_isDecoration = true;

    /**
     * @brief m_searchAction
     * @details 查找action,预设
     */
    QAction *m_searchAction = nullptr;

    /**
     * @brief m_clearAction
     * @details 清除action,预设
     */
    QAction *m_clearAction = nullptr;

    /**
     * @brief m_isSearchButtonEnabled
     * @details 是否显示查找按钮
     */
    bool m_isSearchButtonEnabled = true;

    /**
     * @brief m_isClearButtonEnabled
     * @details 是否显示清除按钮
     */
    bool m_isClearButtonEnabled = true;
};

#endif // ELINEEDITPRIVATE_H
