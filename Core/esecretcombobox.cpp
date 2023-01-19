#include "esecretcombobox.h"

#include "esecretcombobox_p.h"

ESecretComboBox::ESecretComboBox(QWidget *parent):
    QComboBox(parent),
    d_ptr(new ESecretComboBoxPrivate(this))
{
    Q_D(ESecretComboBox);
    d->init();
}

ESecretComboBox::~ESecretComboBox()
{
    Q_D(ESecretComboBox);
    d->deleteLater();
}

int ESecretComboBox::currentLevel() const
{
    Q_D(const ESecretComboBox);
    return d->currentLevel();
}

int ESecretComboBox::findLevel(int level) const
{
    return QComboBox::findData(level);
}

int ESecretComboBox::fromMaskString(const QString &mask) const
{
    Q_D(const ESecretComboBox);
    return d->fromMaskString(mask);
}

QString ESecretComboBox::toString(int level) const
{
    Q_D(const ESecretComboBox);
    return d->toString(level);
}

int ESecretComboBox::toLevel(const QString &text) const
{
    Q_D(const ESecretComboBox);
    return d->toLevel(text);
}

void ESecretComboBox::setTopLevel(int topLevel)
{
    Q_D(ESecretComboBox);
    d->setTopLevel(topLevel);
}

int ESecretComboBox::topLevel() const
{
    Q_D(const ESecretComboBox);
    return d->topLevel();
}

void ESecretComboBox::addItem(int level, const QString &text)
{
    Q_D(ESecretComboBox);
    d->addItem(level,text);
}

void ESecretComboBox::addItems(const QMap<int, QString> &items)
{
    Q_D(ESecretComboBox);
    d->addItems(items);
}

void ESecretComboBox::clear()
{
    Q_D(ESecretComboBox);
    d->clear();
}
