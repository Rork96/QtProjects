#ifndef APPCORE_H
#define APPCORE_H

#include <QUrl>
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
    Q_INVOKABLE bool compressFiles(QObject *window);                // Compress file
    Q_INVOKABLE bool compressDir(QObject *window);                  // Compress dir
    Q_INVOKABLE bool extractArchive(QObject *window);               // Extract archive
    Q_INVOKABLE bool openArchive(QObject *treeView, QUrl fileName); // Open archive
    Q_INVOKABLE bool saveAs(QObject *window);                       // Save archive as
    Q_INVOKABLE void aboutQt();                                     // About Qt
    Q_INVOKABLE void aboutProgram();                                // About program
    Q_INVOKABLE void close();                                       // Brefore closing program

private:
#ifdef Q_OS_WIN
    // Path for temporary files in Windows
    const QString tempPaht = "C:/Users/Default/AppData/Local/Temp/QZiper/";
#endif

#ifdef Q_OS_LINUX
    // Path for temporary files in Linux
    const QString tempPaht = "/tmp/QZiper/";
#endif
};

#endif // APPCORE_H
