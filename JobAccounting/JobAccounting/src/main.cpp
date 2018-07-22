#include "mainwindow.h"
#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Only one copy of the application can be running
    QSystemSemaphore semaphore("JobAccounting", 1);     // Create semaphore
    semaphore.acquire();

#ifndef Q_OS_WIN32
    // Clear memory for linux when application crashed
    QSharedMemory nixMemory("JobAcc");
    if (nixMemory.attach()) {
        nixMemory.detach();
    }
#endif

    QSharedMemory memory("JobAcc"); // Create
    bool isRunning;
    if (memory.attach()) {
        isRunning = true;
    }
    else {
        memory.create(1);
        isRunning = false;
    }
    semaphore.release();    // Release semaphore

    // If one copy is already running
    if (isRunning) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText(QObject::trUtf8("Application is already running.\n"
                                    "You can run only one copy."));
        msg.exec();
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
