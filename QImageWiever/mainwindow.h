#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QShortcut>
#include <QFileInfoList>
#include <QPrintPreviewDialog>
#include <QPushButton>

#include "infodialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Открытие файла при старте программы
    void Open(const QString str);

private:
    // Открыть изображение
    void openImage();

    // Загрузка изображения
    inline void loadImage();

    // Сохранить изображение
    void saveImage();

    // Удалить изображение
    void delImage();

    // Передварительный просмотр печати изображения
    void printImage();

    // Печать
    void print(QPrinter *printer);

    // Следующее изображение
    void nextImage();

    // Предыдущее изображение
    void prevImage();

    // Показ элементов управления
    void showElements(const bool show);

    // Начальное окно приветствия
    void wellcomePage();

    // О программе
    void aboutProgram();

    // О Qt
    void aboutQt();

private:
    Ui::MainWindow *ui;

    // Диалоговое окно
    InfoDialog *infoDlg;

    // QGraphicsView для сцены
    QGraphicsView *gView;

    // Список файлов в  директории
    QFileInfoList dirContent;

    // Текущий индекс файла в dirContent
    int iCurFile = -1;

    // Предыдущее изображение
    QPushButton *prevBtn;

    // Следующее изображение
    QPushButton *nextBtn;

    // Тип отображения изображения
    enum scaleView {
        fitView =0, // Масштаб 100%
        realView    // Вписать изображение
    };

    // Текущий тип отображения изображения
    scaleView ViewType = scaleView ::fitView;

private:
    /* * * Горячие клавиши * * */

    // Открыть изображение
    QShortcut *openShortcut;

    // Сохранить изображение
    QShortcut *saveShortcut;

    // Удалить изображение
    QShortcut *delShortcut;

    // Закрыть изображение
    QShortcut *closeImageShortcut;

    // Печать изображения
    QShortcut *printShortcut;

    // Увеличить изображение
    QShortcut *zoomInShortcut;

    // Уменьшить изображение
    QShortcut *zoomOutShortcut;

    // Масштаб 100%
    QShortcut *realScaleShortcut;

    // Вписать изображение
    QShortcut *fitScaleShortcut;

    // Следующее изображение
    QShortcut *nextImageShortcut;

    // Предыдущее изображение
    QShortcut *prevImageShortcut;

    // Поворот в право на 90 град
    QShortcut *rotRightShortcut;

    // Поворот в лево на 90 град
    QShortcut *rotLeftShortcut;

    // Во весь экран
    QShortcut *fullScrShortcut;

    // О программе
    QShortcut *aboutShortcut;

    // О Qt
    QShortcut *aboutQtShortcut;

    // Масштабирование
#define SCALE_IN    1.25
#define SCALE_OUT   0.8

    // Поворот
#define ROT_RIGHT   90
#define ROT_LEFT    -90
};

#endif // MAINWINDOW_H
