#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LineEdit; }
QT_END_NAMESPACE

class ELineEdit;

class LineEdit : public QWidget
{
    Q_OBJECT

public:
    LineEdit(QWidget *parent = nullptr);
    ~LineEdit();

private:
    Ui::LineEdit *ui;

    ELineEdit *m_edit;
};
#endif // LINEEDIT_H
