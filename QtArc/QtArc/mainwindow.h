#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Library
#include <QArchive.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // Open archive when program starts
    void OpenArc(QString archiveName);

private:
    Ui::MainWindow *ui;
    // Open archive
    void OpenArchive();

};

#endif // MAINWINDOW_H
