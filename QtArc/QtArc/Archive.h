#ifndef Archive_H
#define Archive_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  Copyright (C) 2018 masterarrow <masterarrow@gmail.com>
 *
 *                                          Virtual class Archive
 *                                  (all functions must be pure virtual)
 *
 *  This class created for simplify usage of classes KZip, K7Zip and KTar through single interface,
 *  which minimize repeating code.
 *
 *  Class build on Strategy template for providing a single interface for classes Kzip, K7Zip and KTar.
 *
 *  Use class Archiver for managing archives zip, 7z, tar.gz.
 *
 *  Initialization: Archiver *arc = new Archiver(new AZip)      - for zip files
 *                  Archiver *arc = new Archiver(new A7Zip)     - for 7z files
 *                  Archiver *arc = new Archiver(new ATarGz)    - for tar.gz files
 *
 *  After initialization you will be able to use a functions from it.
 *
 *  Functions:
 *              void setFileName(const QString &filename) - init archive with QString fileName (full file name with path).
 *
 *              bool open(QIODevice::OpenMode mode) - open archive for read or write files. get QIODevice::OpenMode:
 *                                                      QIODevice::ReadOnly, QIODevice::WriteOnly,
 *                                                      returns true if successful.
 *
 *              const KArchiveDirectory* directory() - return KArchiveDirectory* for reading file from archive.
 *
 *              bool writeFile(const QString name, const QByteArray data) - write single file into archive,
 *                                                                          get QString name (full file name with path) and
 *                                                                          QByteArray data (byte array from file),
 *                                                                          returns true if successful.
 *
 *              bool close() - close archive after usage (it's necessary!), returns true if successful.
 *
 *  Warning !!! : always close archive after usage - acr->close()
 *
 *  Each function from child class AZip, A7Zip and ATar call function from class KZip, K7Zip and KTar.
 *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <kzip.h>                   // zip
#include <k7zip.h>                  // 7z
#include <ktar.h>                   // tar.gz

class Archive {
public:
    // All funcions pure virtual = 0 (default)
    virtual ~Archive() = default;
    virtual void setFileName(const QString &filename) = 0;
    virtual bool open(QIODevice::OpenMode mode) = 0;
    virtual const KArchiveDirectory* directory() const = 0;
    virtual bool writeFile(const QString name, const QByteArray data)= 0;
    virtual bool close() = 0;
};

/* For zip archives (it use KZip) */
class AZip : public Archive {
public:
    ~AZip() { delete  zip; }
    void setFileName(const QString &filename){
        zip = new KZip(filename);   // Init KZip
    }
    bool open(QIODevice::OpenMode mode) {
        return zip->open(mode);     // Open acrhive for read or write
    }
    const KArchiveDirectory* directory() const {
        return zip->directory();    // Get archive directory for reading files
    }
    bool writeFile(const QString name, const QByteArray data) {
        return zip->writeFile(name, data);  // Write file into archive
    }
    bool close() {
        bool result = zip->close();     // Close archive!
        if (result) {
            delete zip;
            return result;
        }
        return result;
    }
private:
    KZip *zip;
};

/* For 7z archives (it use K7Zip) */
class A7Zip : public Archive {
public:
    ~A7Zip() { delete  sZip; }
    void setFileName(const QString &filename){
        sZip = new K7Zip(filename);
    }
    bool open(QIODevice::OpenMode mode) {
        return sZip->open(mode);
    }
    const KArchiveDirectory* directory() const {
        return sZip->directory();
    }
    bool writeFile(const QString name, const QByteArray data) {
        return sZip->writeFile(name, data);
    }
    bool close() {
        bool result = sZip->close();
        if (result) {
            delete sZip;
            return result;
        }
        return result;
    }
private:
    K7Zip *sZip;
};

/* For tar.gz archives (it use KTar) */
class ATarGz : public Archive {
public:
    ~ATarGz() { delete  tar; }
    void setFileName(const QString &filename){
        tar = new KTar(filename);
    }
    bool open(QIODevice::OpenMode mode) {
        return tar->open(mode);
    }
    const KArchiveDirectory* directory() const {
        return tar->directory();
    }
    bool writeFile(const QString name, const QByteArray data) {
        return tar->writeFile(name, data);
    }
    bool close() {
        bool result = tar->close();
        if (result) {
            delete tar;
            return result;
        }
        return result;
    }
private:
    KTar *tar;
};

// Use for managing archives
class Archiver {
public:
    // Archiver *arc = new Archiver(new AZip)   - zip
    // Archiver *arc = new Archiver(new A7Zip)  - 7z
    // Archiver *arc = new Archiver(new ATarGz) - tar.gz
    Archiver(Archive *archive) : arc(archive) {}
    ~Archiver() { delete  arc; }
    void setFileName(const QString &filename) {
        arc->setFileName(filename);
    }
    bool open(QIODevice::OpenMode mode) {
        return arc->open(mode);
    }
    const KArchiveDirectory* directory() const {
        return arc->directory();
    }
    bool writeFile(const QString name, const QByteArray data) {
        return arc->writeFile(name, data);
    }
    bool close() {
        return arc->close();
    }
private:
    Archive *arc;
};

#endif //Archive_H