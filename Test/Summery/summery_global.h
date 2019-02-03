#ifndef SUMMERY_GLOBAL_H
#define SUMMERY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SUMMERY_LIBRARY)
#  define SUMMERYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SUMMERYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUMMERY_GLOBAL_H
