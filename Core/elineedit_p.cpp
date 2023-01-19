#include "elineedit_p.h"

#include <QAction>
#include <QIcon>

#include "elineedit.h"

ELineEditPrivate::ELineEditPrivate(ELineEdit *parent):
    q_ptr(parent)
{
}

void ELineEditPrivate::init()
{
    Q_Q(ELineEdit);
    m_searchAction = q->addAction(QIcon(":/resources/search.png"),QLineEdit::LeadingPosition);
    m_clearAction = q->addAction(QIcon(":/resources/clear.png"),QLineEdit::TrailingPosition);

    m_clearAction->setVisible(m_isClearButtonEnabled);
    m_searchAction->setVisible(m_isSearchButtonEnabled);

    m_clearAction->setVisible((!q->text().isEmpty()) && isClearButtonEnabled());

    connect(m_searchAction,&QAction::triggered,q,&ELineEdit::searchButtonPressed);
    connect(m_clearAction,&QAction::triggered,q,&ELineEdit::clear);
    connect(q,&ELineEdit::textChanged,this,[=](){
            m_clearAction->setVisible((!(q->text().isEmpty())) && isClearButtonEnabled());
    });

    connect(q,&ELineEdit::returnPressed,q,&ELineEdit::searchButtonPressed);

    connect(q,&QLineEdit::textChanged,q,[=](const QString &text){
        emit q->textChanged(isDecoration() ? text.trimmed() : text);
    });
    connect(q,&QLineEdit::textEdited,q,[=](const QString &text){
        emit q->textChanged(isDecoration() ? text.trimmed() : text);
    });

}

void ELineEditPrivate::setDecoration(bool enabled)
{
    m_isDecoration = enabled;
}

bool ELineEditPrivate::isDecoration() const
{
    return  m_isDecoration;
}

void ELineEditPrivate::setClearButtonEnabled(bool enabled)
{
    m_isClearButtonEnabled = enabled;
    m_clearAction->setVisible(enabled);
}

bool ELineEditPrivate::isClearButtonEnabled() const
{
    return m_isClearButtonEnabled;
}

void ELineEditPrivate::setSearchButtonEnabled(bool enabled)
{
    m_isSearchButtonEnabled = enabled;
    m_searchAction->setVisible(enabled);
}

bool ELineEditPrivate::isSearchButtonEnabled() const
{
    return m_isSearchButtonEnabled;
}
