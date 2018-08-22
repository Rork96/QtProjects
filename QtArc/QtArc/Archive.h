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
 *  Class build on Strategy template for providing a single and simple interface for classes Kzip, K7Zip and KTar.
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
 *              bool addLocalFile(const QString &fileName, const QString &destName) - write (add) a single file into archive,
 *                                                                          get fileName (full file name with path) and
 *                                                                          destName (name in the archive),
 *                                                                          returns true if successful.
 *
 *              bool addLocalDirectory(const QString &path, const QString &destName) - write (add) a directory into archive
 *                                                                          with all its contents (recursively),
 *                                                                          get path (full dir name with path) and
 *                                                                          destName (name in the archive),
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

// region Main class (virtual)

class Archive {
public:
    // All functions pure virtual = 0 (default)
    virtual ~Archive() = default;
    virtual void setFileName(const QString &filename) = 0;
    virtual bool open(QIODevice::OpenMode mode) = 0;
    virtual const KArchiveDirectory* directory() const = 0;
    virtual bool addLocalFile(const QString &fileName, const QString &destName) = 0;
    virtual bool addLocalDirectory(const QString &path, const QString &destName) = 0;
    virtual bool close() = 0;
};
// endregion Main

// region For zip archives (it use KZip)

class AZip : public Archive {
public:
    ~AZip() override { delete  zip; }
    void setFileName(const QString &filename) override {
        zip = new KZip(filename);   // Init KZip
    }
    bool open(QIODevice::OpenMode mode) override {
        return zip->open(mode);     // Open acrhive for read or write
    }
    const KArchiveDirectory* directory() const override {
        return zip->directory();    // Get archive directory for reading files
    }
    bool addLocalFile(const QString &fileName, const QString &destName) override {
        return zip->addLocalFile(fileName, destName);   // Write file into archive
    }
    bool addLocalDirectory(const QString &path, const QString &destName) override {
        return zip->addLocalDirectory(path, destName); // Write dir into archive
    }
    bool close() override {
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
// endregion zip

// region For 7z archives (it use K7Zip)

class A7Zip : public Archive {
public:
    ~A7Zip() override { delete  sZip; }
    void setFileName(const QString &filename) override {
        sZip = new K7Zip(filename);
    }
    bool open(QIODevice::OpenMode mode) override {
        return sZip->open(mode);
    }
    const KArchiveDirectory* directory() const override {
        return sZip->directory();
    }
    bool addLocalFile(const QString &fileName, const QString &destName) override {
        return sZip->addLocalFile(fileName, destName);
    }
    bool addLocalDirectory(const QString &path, const QString &destName) override {
        return sZip->addLocalDirectory(path, destName);
    }
    bool close() override {
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
// endregion 7z

// region For tar.gz archives (it use KTar)

class ATarGz : public Archive {
public:
    ~ATarGz() override { delete  tar; }
    void setFileName(const QString &filename) override {
        tar = new KTar(filename);
    }
    bool open(QIODevice::OpenMode mode) override {
        return tar->open(mode);
    }
    const KArchiveDirectory* directory() const override {
        return tar->directory();
    }
    bool addLocalFile(const QString &fileName, const QString &destName) override {
        return tar->addLocalFile(fileName, destName);
    }
    bool addLocalDirectory(const QString &path, const QString &destName) override {
        return tar->addLocalDirectory(path, destName);
    }
    bool close() override {
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
// endregion tar.gz

// region Archiver (use for managing archives)

class Archiver {
public:
    // Archiver *arc = new Archiver(new AZip)   - zip
    // Archiver *arc = new Archiver(new A7Zip)  - 7z
    // Archiver *arc = new Archiver(new ATarGz) - tar.gz
    explicit Archiver(Archive *archive) : arc(archive) {}
    ~Archiver() { delete  arc; }
    void setFileName(const QString &filename) {
        arc->setFileName(filename);
    }
    bool open(QIODevice::OpenMode mode) {
        return arc->open(mode);
    }
    const KArchiveDirectory *directory() const {
        return arc->directory();
    }
    bool addLocalFile(const QString &fileName, const QString &destName) {
        return arc->addLocalFile(fileName, destName);
    }
    bool addLocalDirectory(const QString &path, const QString &destName) {
        return arc->addLocalDirectory(path, destName);
    }
    bool close() {
        return arc->close();
    }
private:
    Archive *arc;
};
// endregion Archiver

#endif //Archive_H