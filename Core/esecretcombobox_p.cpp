#include "esecretcombobox_p.h"

#include "esecretcombobox.h"

//默认密集范围
static const QMap<int ,QString> DEFAULT_LEVELS{
    {0,QT_TR_NOOP("非密")},
    {1,QT_TR_NOOP("秘密")},
    {2,QT_TR_NOOP("机密")},
    {3,QT_TR_NOOP("绝密")}
};

static const QMap<QString,QString> MASK_MAP{
    {"fm",QT_TR_NOOP("非密")},
    {"mm",QT_TR_NOOP("秘密")},
    {"jj",QT_TR_NOOP("机密")},
    {"jm",QT_TR_NOOP("绝密")}
};

ESecretComboBoxPrivate::ESecretComboBoxPrivate(ESecretComboBox *parent):
    q_ptr(parent)
{
}

/**
 * @brief ESecretComboBoxPrivate::currentLevel
 * @return 返回当前的密级值，如果没找到返回-1。
 */
int ESecretComboBoxPrivate::currentLevel() const
{
    Q_Q(const ESecretComboBox);
    int level = -1;
    auto variant = q->currentData();
    if(variant.isValid())
    {
        level = variant.toInt();
    }

    return level;
}

/**
 * @brief init
 * @details 初始化界面
 */
void ESecretComboBoxPrivate::init()
{
    for(auto begin = DEFAULT_LEVELS.constBegin(); begin != DEFAULT_LEVELS.constEnd(); ++begin)
    {
        auto key = begin.key();
        auto value = begin.value();

        m_levels.insert(key,value);
    }

    updateItems();
}

/**
 * @brief setTopLevel
 * @param topLevel 最顶层的级别
 * @details 设置mj的最高级别，超过此级别的mj选项不显示,允许设置0~255个密级，设置超过此范围的数按照边界值设定
 */
void ESecretComboBoxPrivate::setTopLevel(int topLevel)
{
    if(topLevel < 0)
    {
        m_topLevel = 0;
    }
    else if(topLevel > 255)
    {
        m_topLevel = 255;
    }
    else
    {
        m_topLevel = topLevel;
    }

    updateItems();
}

/**
 * @brief addItems
 * @param items mj等级以及对应显示的文本
 * @details items的key值表示其等级，key值越高，mj就越高，其value是对应mj所显示的文本
 */
void ESecretComboBoxPrivate::addItems(const QMap<int, QString> &items)
{
    for(auto begin = items.constBegin(); begin != items.constEnd(); ++begin)
    {
        auto key = begin.key();
        auto value = begin.value();

        m_levels.insert(key,value);
    }
    updateItems();
}


/**
 * @brief addItem
 * @param level 权限等级
 * @param text	权限显示的文本
 */
void ESecretComboBoxPrivate::addItem(int level, const QString &text)
{
    m_levels.insert(level,text);
    updateItems();
}

/**
 * @brief updateItems
 * @details 更新密级选项显示
 */
void ESecretComboBoxPrivate::updateItems()
{
    Q_Q(ESecretComboBox);
    q->QComboBox::clear();
    auto items = this->items();
    for(auto begin = items.constBegin(); begin != items.constEnd(); ++begin)
    {
        auto key = begin.key();
        auto value = begin.value();
        if(topLevel() < key)
        {
            break;
        }

        q->QComboBox::addItem(value,key);
    }
}

/**
 * @brief clear
 * @details 清空选项
 */
void ESecretComboBoxPrivate::clear()
{
    Q_Q(ESecretComboBox);
    q->QComboBox::clear();
    m_levels.clear();
}

QString ESecretComboBoxPrivate::toString(int level) const
{
    return m_levels.value(level,"");
}

int ESecretComboBoxPrivate::toLevel(const QString &text) const
{
    return m_levels.key(text,-1);
}

/**
 * @brief ESecretComboBoxPrivate::fromMaskString
 * @param mask
 * @return 返回mask对应的密级值，没有对应的mask，则返回-1。
 */
int ESecretComboBoxPrivate::fromMaskString(const QString &mask) const
{
    return m_levels.key(MASK_MAP.value(mask,""),-1);
}
