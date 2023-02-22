#include "ecalendartimewidget.h"
#include "ecalendartimewidget_p.h"
#include "ETimeWidget"

#include <QLayout>

ECalendarTimeWidget::ECalendarTimeWidget(QWidget *parent) :
    QCalendarWidget(parent),
    d_ptr(new ECalendarTimeWidgetPrivate(this))
{
    Q_D(ECalendarTimeWidget);
    QCalendarWidget::layout()->addWidget(d->timeWidget());

    setLayout(QCalendarWidget::layout());
}

ECalendarTimeWidget::~ECalendarTimeWidget()
{

}

QSize ECalendarTimeWidget::sizeHint() const
{
    Q_D(const ECalendarTimeWidget);
    auto size = QCalendarWidget::sizeHint();
    size.setHeight(size.height() + d->timeWidget()->sizeHint().height());
    return size;
}
