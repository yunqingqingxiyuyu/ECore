#include "etimewidget.h"

#include "etimewidget_p.h"

ETimeWidget::ETimeWidget(const QTime &time,QWidget *parent):
    QWidget(parent),
    d_ptr(new ETimeWidgetPrivate(time,this))
{

}

ETimeWidget::~ETimeWidget()
{

}
