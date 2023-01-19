#ifndef ESECRETCOMBOBOX_H
#define ESECRETCOMBOBOX_H

#include "core_global.h"
#include <QComboBox>

class ESecretComboBoxPrivate;

class CORE_EXPORT ESecretComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ESecretComboBox(QWidget *parent = nullptr);
    virtual ~ESecretComboBox();

    /**
     * @brief currentLevel
     * @return 返回当前选择的密级,如果为空或者没有被选择，则返回为-1。
     */
    int currentLevel() const;

    /**
     * @brief findLevel
     * @param level
     * @return 查找level密级对应的索引值，没有找到就返回-1。
     */
    int findLevel(int level) const;

    /**
     * @brief fromMaskString
     * @param mask 密级的掩码，比如"机 密"使用"jm"替代，jm即为其mask
     * @return 返回mask所对应的密级值,没有找到就返回-1。
     */
    int fromMaskString(const QString &mask) const;

    /**
     * @brief toString
     * @param level 密级值
     * @return 返回level密级值所对应的显示文本。例如默认情况下，mj值为0对应的文本为"非 密"。找不到返回""。
     */
    QString toString(int level) const;

    /**
     * @brief toLevel
     * @param text mj显示的文本
     * @return 返回text对应mj的mj值，找不到返回-1。
     */
    int toLevel(const QString &text) const;

    /**
     * @brief setTopLevel
     * @param topLevel 最顶层的级别
     * @details 设置mj的最高级别，超过此级别的mj选项不显示,允许设置0~255个密级，设置超过此范围的数按照边界值设定
     */
    void setTopLevel(int topLevel = 255);

    /**
     * @brief topLevel
     * @return 返回允许显示的最高密级
     */
    int topLevel() const;

    /**
     * @brief addItems
     * @param items mj等级以及对应显示的文本
     * @details items的key值表示其等级，key值越高，mj就越高，其value是对应mj所显示的文本
     */
    void addItems(const QMap<int ,QString> &items);

    /**
     * @brief addItem
     * @param level 权限等级
     * @param text	权限显示的文本
     */
    void addItem(int level,const QString &text);

    /**
     * @brief clear
     * @details 清空选项
     */
    void clear();

private:
    Q_DISABLE_COPY(ESecretComboBox);
    ESecretComboBoxPrivate *d_ptr = nullptr;
    Q_DECLARE_PRIVATE(ESecretComboBox);
};

#endif // ESECRETCOMBOBOX_H
