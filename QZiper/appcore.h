#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QFileSystemModel>

class AppCore : public QObject
{
    Q_OBJECT
    using BaseClass = QObject;
public:
    explicit AppCore(QObject *parent = nullptr);

public:
    // Receive data from qml - Q_INVOKABLE
    // or public slots
    Q_INVOKABLE void compressFiles();   // Compress file
    Q_INVOKABLE void compressDir();     // Compress dir
    Q_INVOKABLE void extractArchive();  // Extract archive
    Q_INVOKABLE void openArchive();     // Open archive -
    Q_INVOKABLE void aboutQt();         // About Qt
    Q_INVOKABLE void aboutProgram();    // About program
    QFileSystemModel fileSystemModel;
};

#endif // APPCORE_H
