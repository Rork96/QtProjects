#include "Archive.h"

Archive::Archive(int context)
{
    this->context = context;
}

template <class T>
T Archive::getObject(const QString &filename)
{
    switch (context) {
        case 0 : {
            K7Zip sevenZip(filename);
            return sevenZip;
        }
        case 1 : {
            KTar tar(filename);
            return tar;
        }
        default: {
            KZip zip(filename);
            return zip;
        }
    }
}