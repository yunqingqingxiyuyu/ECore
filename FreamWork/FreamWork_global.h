#ifndef FREAMWORK_GLOBAL_H
#define FREAMWORK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FREAMWORK_LIBRARY)
#  define FREAMWORK_EXPORT Q_DECL_EXPORT
#else
#  define FREAMWORK_EXPORT Q_DECL_IMPORT
#endif

#endif // FREAMWORK_GLOBAL_H
