#ifndef Archive_H
#define Archive_H

#include <QObject>

#include <kzip.h>                   // zip
#include <k7zip.h>                  // 7zip
#include <ktar.h>                   // tar.gz
#include <kcompressiondevice.h>     // bz2

class KARCHIVE_EXPORT Archive {

public:
    explicit Archive(int context);

    template <class T>
    T getObject(const QString &filename);

    int context = 0; // 0 = zip, 1 = 7zip, 2 = tar

    signals:

public
    slots:
};

#endif //Archive_H