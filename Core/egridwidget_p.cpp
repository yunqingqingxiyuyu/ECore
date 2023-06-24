#include "egridwidget_p.h"

#include "egridwidget.h"


EGridWidgetPrivate::EGridWidgetPrivate(EGridWidget *parent):
    q_ptr(parent)
{
    if(parent)
        labelFont = parent->font();
}

EGridWidgetPrivate::~EGridWidgetPrivate()
{

}


