#include "elineedit_p.h"

#include <QAction>
#include <QIcon>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

#include "elineedit.h"

ELineEditPrivate::ELineEditPrivate(ELineEdit *parent):
    q_ptr(parent)
{
}

ELineEditPrivate::~ELineEditPrivate()
{
}

void ELineEditPrivate::init()
{
    Q_Q(ELineEdit);

    q->setMaxLength(20);

    QRegularExpression re;
    re.setPattern("[^\\s]*");

    m_defaultValidator = new QRegularExpressionValidator(re,this);
    q->QLineEdit::setValidator(m_defaultValidator);

    m_searchAction = q->addAction(QIcon(":/resources/search.png"),QLineEdit::LeadingPosition);
    m_clearAction = q->addAction(QIcon(":/resources/clear.png"),QLineEdit::TrailingPosition);

    m_clearAction->setVisible(m_isClearButtonEnabled);
    m_searchAction->setVisible(m_isSearchButtonEnabled);

    m_clearAction->setVisible((!q->text().isEmpty()) && isClearButtonEnabled());

    connect(m_searchAction,&QAction::triggered,this,&ELineEditPrivate::searchButtonPressed);
    connect(m_clearAction,&QAction::triggered,q,&ELineEdit::clear);
    connect(q,&ELineEdit::textChanged,this,[=](){
            m_clearAction->setVisible((!(q->text().isEmpty())) && isClearButtonEnabled());
    });

    connect(q,&ELineEdit::returnPressed,this,&ELineEditPrivate::searchButtonPressed);

    connect(q,&QLineEdit::textChanged,q,[=](const QString &text){
        emit q->textChanged(isDecoration() ? text.trimmed() : text);
    });
    connect(q,&QLineEdit::textEdited,q,[=](const QString &text){
        emit q->textChanged(isDecoration() ? text.trimmed() : text);
    });

}


void ELineEditPrivate::searchButtonPressed()
{
    Q_Q(ELineEdit);
    emit q->searchPressed(q->text());
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
