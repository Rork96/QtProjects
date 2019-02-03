#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QShortcut>
#include <QPrintPreviewDialog>

#ifdef Q_OS_WIN
    #include "windows.h"
#endif

#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionDarkColor_triggered();

    void on_actionWhiteColor_triggered();

    void on_actionRedColor_triggered();

    void on_actionGreenColor_triggered();

    void on_actionBlooColor_triggered();

    void on_actionYellowColor_triggered();

    void on_actionPen_triggered();

    void on_actionLine_triggered();

    void on_actionElipse_triggered();

    void on_actionRectangle_triggered();

    void on_actionText_triggered();

    void on_actionCut_triggered();

    void on_actionApply_triggered();

    void on_actionCancel_triggered();

    void on_actionCursor_triggered();

    void on_actionPrint_triggered();

protected:
    // Метод для обработки native событий от ОС в Qt
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::MainWindow *ui;

    // Снимок экрана
    void printScrean();
    // Сохранить снимок экрана
    void saveScrean();
    // Показать инконку в трее
    void showTrayIcon();
    // Смена состояния окна (сворачивание)
    void changeEvent(QEvent *event);
    // Закрытие окна
    void closeEvent(QCloseEvent *event);
    // Печать
    void print(QPrinter *printer);

    // Иконка в трее
    QSystemTrayIcon *trayIcon;
    // Сцена для рисования
    PaintScene *scene;
    // Отмена предыдущего действия
    QShortcut *retShortcut;

    // Масштабирование
#define SCALE_IN    1.25
#define SCALE_OUT   0.8
};

#endif // MAINWINDOW_H
