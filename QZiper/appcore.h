#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
    using BaseClass = QObject;
public:
    explicit AppCore(QObject *parent = nullptr);

public:
    // Receive data from qml - Q_INVOKABLE
    // or public slots
    Q_INVOKABLE void compressFiles(QStringList QStringList, QString ArchiveName);   // Compress file
    Q_INVOKABLE void compressDir(QString DirName, QString ArchiveName);             // Compress dir
    Q_INVOKABLE void extractArchive(QString ArchiveName, QString DirName);          // Extract archive
    Q_INVOKABLE void openArchive(QString ArchiveName);                              // Open archive
    Q_INVOKABLE void aboutQt();                                                     // About Qt
    Q_INVOKABLE void aboutProgram();                                                // About program
};

#endif // APPCORE_H
