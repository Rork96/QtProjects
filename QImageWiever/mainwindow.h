#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QShortcut>
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QFileInfoList>

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

private:
    Ui::MainWindow *ui;

    // QGraphicsView для сцены
    QGraphicsView *gView;
    // Сцена для помещение в нее изображения
    QGraphicsScene *scene;

    // Сочетание клавиш и действие для открытия изображения
    QShortcut *openShortcut;
    QAction *openAction;

    // Сочетание клавиш и действие для сохранения изображения
    QShortcut *saveShortcut;
    QAction *saveAction;

    // Сочетание клавиш и действие для увеличения изображения
    QShortcut *zoomInShortcut;
    QAction *zoomInAction;

    // Сочетание клавиш и действие для уменьшения изображения
    QShortcut *zoomOutShortcut;
    QAction *zoomOutAction;

    // Следующее изображение
    QShortcut *nextImageShortcut;
    QAction *nextImageAction;

    // Предыдущее изображение
    QShortcut *prevImageShortcut;
    QAction *prevImageAction;

    // Список файлов в  директории
    QFileInfoList dirContent;
    // Текущий индекс файла в dirContent
    int iCurFile = -1;

    // Поворот в право на 90 град
    QShortcut *rotRightShortcut;
    QAction *rotRightAction;

    // Поворот в лево на 90 град
    QShortcut *rotLeftShortcut;
    QAction *rotLeftAction;

    // Масштабирование
#define SCALE_IN    1.25
#define SCALE_OUT   0.8
    // Поворот
#define ROT_RIGHT   90
#define ROT_LEFT    -90
};

#endif // MAINWINDOW_H
