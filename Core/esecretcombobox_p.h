#ifndef ESECRETCOMBOBOX_P_H
#define ESECRETCOMBOBOX_P_H

#include <QObject>
#include <QMap>

class ESecretComboBox;

class ESecretComboBoxPrivate : public QObject
{
    Q_OBJECT
    ESecretComboBox *const q_ptr;
    Q_DISABLE_COPY(ESecretComboBoxPrivate);
    Q_DECLARE_PUBLIC(ESecretComboBox);

public:
    explicit ESecretComboBoxPrivate(ESecretComboBox *parent);

    int currentLevel() const;

    void setTopLevel(int topLevel);

    int topLevel() const {return m_topLevel;}

    void addItems(const QMap<int ,QString> &items);

    void addItem(int level,const QString &text);

    void clear();

    int fromMaskString(const QString &mask) const;

    QString toString(int level) const;

    int toLevel(const QString &text) const;

private:
    void init();

    void updateItems();

    /**
     * @brief items
     * @return 返回密级以及其对应的文本
     */
    QMap<int ,QString> items() const{return m_levels;}
private:
    /**
     * @brief m_levels
     * @details 存储密级以及对应显示的文本
     */
    QMap<int ,QString> m_levels;

    /**
     * @brief m_topLevel
     * @details 允许显示的最高密级，高于本密级的项不显示
     */
    int m_topLevel = 255;
};

#endif // ESECRETCOMBOBOX_H
