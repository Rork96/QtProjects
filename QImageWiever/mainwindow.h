#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QShortcut>
#include <QGraphicsPixmapItem>
#include <QFileInfoList>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // Открыть изображение
    void openImage();

    // Загрузка изображения
    inline void loadImage(const QString& str);

    // Сохранить изображение
    void saveImage();

    // Следующее изображение
    void nextImage();

    // Предыдущее изображение
    void prevImage();

    // О программе
    void aboutProgram();

private:
    Ui::MainWindow *ui;

    // QGraphicsView для сцены
    QGraphicsView *gView;

    // Сцена для помещение в нее изображения
    QGraphicsScene *scene;

    // Список файлов в  директории
    QFileInfoList dirContent;

    // Текущий индекс файла в dirContent
    int iCurFile = -1;

    // Предыдущее изображение
    QPushButton *rBtn;

    // Следующее изображение
    QPushButton *lBtn;

private:
    /* * * Горячие клавиши * * */

    // Открыть изображение
    QShortcut *openShortcut;

    // Сохранить изображение
    QShortcut *saveShortcut;

    // Увеличить изображение
    QShortcut *zoomInShortcut;

    // Уменьшить изображение
    QShortcut *zoomOutShortcut;

    // Следующее изображение
    QShortcut *nextImageShortcut;

    // Предыдущее изображение
    QShortcut *prevImageShortcut;

    // Поворот в право на 90 град
    QShortcut *rotRightShortcut;

    // Поворот в лево на 90 град
    QShortcut *rotLeftShortcut;

    // Показать элементы управления
    void showElements();

    // О программе
    QAction *aboutAction;

    // Масштабирование
#define SCALE_IN    1.25
#define SCALE_OUT   0.8

    // Поворот
#define ROT_RIGHT   90
#define ROT_LEFT    -90
};

#endif // MAINWINDOW_H
