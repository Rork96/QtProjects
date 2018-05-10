#ifndef Archive_H
#define Archive_H

#include <QObject>

#include <kzip.h>                   // zip
#include <k7zip.h>                  // 7zip
#include <ktar.h>                   // tar.gz
#include <kcompressiondevice.h>     // bz2

class Archive {

public:
    virtual ~Archive() {}
    virtual void open(const QString &filename, QIODevice::OpenMode mode) = 0;
};

class AZip : public Archive {
public:
    void open(const QString &filename, QIODevice::OpenMode mode) {
        KZip zip(filename);
        zip.open(mode);
    }
};

class A7Zip : public Archive {
public:
    void open(const QString &filename, QIODevice::OpenMode mode) {
        KZip zip(filename);
        zip.open(mode);
    }
};

class ATar : public Archive {
public:
    void open(const QString &filename, QIODevice::OpenMode mode) {
        KZip zip(filename);
        zip.open(mode);
    }
};

class Archiver {
public:
    Archiver(Archive *archive) : arc(archive) {}
    ~Archiver() { delete  arc; }
    void open(const QString &filename, QIODevice::OpenMode mode) {
        arc->open(filename, mode);
    }
private:
    Archive *arc;
};

#endif //Archive_H