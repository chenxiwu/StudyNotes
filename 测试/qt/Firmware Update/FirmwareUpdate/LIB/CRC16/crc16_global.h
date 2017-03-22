#ifndef CRC16_GLOBAL_H
#define CRC16_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRC16_LIBRARY)
#  define CRC16SHARED_EXPORT Q_DECL_EXPORT
#else
#  define CRC16SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CRC16_GLOBAL_H
