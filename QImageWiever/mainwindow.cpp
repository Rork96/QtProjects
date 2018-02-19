#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Окно развернуто на весь экран
    setWindowState(Qt::WindowMaximized);

    //ui->gridLayout->setContentsMargins(0, 0, 0, 0);

    // Черный цвер фона
    /*QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);*/
    setStyleSheet("background-color:black;");

    // Установка QGraphicsView и QGraphicsScene
    // для отображения изображения
    gView = new QGraphicsView();
    setCentralWidget(gView);
    scene = new QGraphicsScene();
    gView->setScene(scene);
    // Элемент для отображения изображения
    /*pixItem = new QGraphicsPixmapItem();
    scene->addItem(pixItem);
    pixItem->setVisible(true);*/

    // Сочетание клавиш и действие для открытия изображения
    openShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
    openAction = new QAction("Открыть изображение", this);

    // Сочетание клавиш и действие для сохранения изображения
    saveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);;
    saveAction = new QAction("Открыть изображение", this);;

    // Сочетание клавиш и действие для увеличения изображения
    zoomInShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus), this);
    zoomInAction = new QAction("Увеличить", this);

    // Сочетание клавиш и действие для уменьшения изображения
    zoomOutShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), this);
    zoomOutAction = new QAction("Уменьшить", this);

    // Следующее изображение
    nextImageShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    nextImageAction = new QAction("Следующее изображение", this);

    // Предыдущее изображение
    prevImageShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    prevImageAction = new QAction("Предыдущее изображение", this);

    // Поворот в право на 90 град
    rotRightShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right), this);
    rotRightAction = new QAction("Повернуть в право", this);

    // Поворот в лево на 90 град
    rotLeftShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left), this);
    rotLeftAction = new QAction("Повернуть в лево", this);

    /* Слоты */ {
        // Открыть изображение
        connect(openShortcut, &QShortcut::activated, this, &MainWindow::openImage);
        connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

        // Соханить изображение
        connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveImage);
        connect(saveAction, &QAction::triggered, this, &MainWindow::saveImage);

        // Увеличить
        connect(zoomInShortcut, &QShortcut::activated, this, [this] {
            gView->scale(SCALE_IN, SCALE_IN);
        });
        connect(zoomInAction, &QAction::triggered, this, [this] {
            gView->scale(SCALE_IN, SCALE_IN);
        });
        // Уменьшить
        connect(zoomOutShortcut, &QShortcut::activated, this, [this] {
            gView->scale(SCALE_OUT, SCALE_OUT);
        });
        connect(zoomOutAction, &QAction::triggered, this, [this] {
            gView->scale(SCALE_OUT, SCALE_OUT);
        });

        // Следующее изображение
        connect(nextImageShortcut, &QShortcut::activated, this, &MainWindow::nextImage);
        connect(nextImageAction, &QAction::triggered, this, &MainWindow::nextImage);

        // Предыдущее изображение
        connect(prevImageShortcut, &QShortcut::activated, this, &MainWindow::prevImage);
        connect(prevImageAction, &QAction::triggered, this, &MainWindow::prevImage);

        // Поворот в право на 90 град
        connect(rotRightShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_RIGHT);
        });
        connect(rotRightAction, &QAction::triggered, this, [this] {
            gView->rotate(ROT_RIGHT);
        });

        // Поворот в лево на 90 град
        connect(rotLeftShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_LEFT);
        });
        connect(rotLeftAction, &QAction::triggered, this, [this] {
            gView->rotate(ROT_LEFT);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{
    // Открыть изображение
    QString fName = QFileDialog::getOpenFileName(this, "Открыть изображение",
                QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                            "Файлы изображений (*.jpg | *.jpeg | *.png)");

    if(fName.isEmpty()) return;

    // Получить все файлы директории
    QDir dir(QFileInfo(fName).absoluteDir());
    dirContent = dir.entryInfoList(QStringList() << "*.jpg" << "*.jpeg" << "*.png",
                                                 QDir::Files | QDir::NoDotAndDotDot);

    // Сохранить индекс выбранного изображения
    iCurFile = dirContent.indexOf(QFileInfo(fName), 0);
    // Отобразить выбранное изображение
    loadImage(fName);
    /*pixItem->setPixmap(QPixmap(fName));
    // Подгонка изображения под размер сцены
    gView->setSceneRect(0, 0, QPixmap(fName).width(), QPixmap(fName).height());
    gView->fitInView(pixItem, Qt::KeepAspectRatio);
     */
}

inline void MainWindow::loadImage(const QString& str)
{
    // Загрузка изображения
    QPixmap pix(str);

    // Добавить новый элемент на сцену
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem();
    scene->addItem(pixItem);

    // Получить все элементы в сцены
    QList<QGraphicsItem *> item = scene->items();

    // Если в сцене больше одного элемента, то
    // удалить предыдущий
    if(item.count() > 1) delete item.last();

    /*
     *
     *
     * Не верно обрабатываются изображения размером больше, чем размер сцены,
     * с меньшими похоже все в порядке (нужно больше тестирования)
     *
     *
     *
     */

    // Если размер изображения больше размеров сцены в которую оно помещается, то
    if( (QPixmap(str).width() >= scene->width()) || (QPixmap(str).height() >= scene->height()) ) {
        // подогнать изображение под размер сцены
        //gView->setSceneRect(0, 0, QPixmap(str).width(), QPixmap(str).height());
        //gView->fitInView(pixItem, Qt::KeepAspectRatio);
        pixItem->setVisible(true);
        pixItem->setPixmap(QPixmap(str));
    }
    else {
        // подогнать сцену под размер изображения
        //gView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
        //gView->fitInView(scene->sceneRect());

        pixItem->setVisible(true);
        pixItem->setPixmap(QPixmap(str));
        gView->setSceneRect(0, 0, QPixmap(str).width(), QPixmap(str).height());
        gView->fitInView(pixItem, Qt::KeepAspectRatio);
    }
    /*
    pixItem->setVisible(true);
    pixItem->setPixmap(QPixmap(str));
     */

    // Имя файла в заголовке окна
    setWindowTitle("QImageWiever - " + QFileInfo(str).fileName());
}

void MainWindow::saveImage()
{
    // Сохранить изображение

    if(iCurFile == -1) return; // Нет открытых изображений

    // Открытый файл
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    QFile f(str);

    /*
     *
     * Имя файла по умолчанию
     *
     */

    // Имя и путь к новому файлу
    QString fName = QFileDialog::getSaveFileName(this, "Открыть изображение",
               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                           "Файлы изображений (*.jpg | *.jpeg |*.png *)");

    if(fName.isEmpty()) return;

    // Добавить расширение если его нет
#ifdef Q_OS_LINUX
    if(QFileInfo(fName).suffix() == "") fName += ".jpg";
#endif

    // Сохранить изображение
    f.copy(fName);
}

void MainWindow::nextImage()
{
    // Следующее изображение

    if(iCurFile == -1) return; // Нет открытых изображений

    iCurFile++;

    // Дойдя до окнца списка, перейти к первоу изображению
    if(iCurFile > dirContent.indexOf(dirContent.last(), 0)) {
        iCurFile = dirContent.indexOf(dirContent.first(), 0);
    }

    // Загрузить изображение
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    loadImage(str);
}

void MainWindow::prevImage()
{
    // Предыдущее изображение

    if(iCurFile == -1) return; // Нет открытых изображений

    iCurFile--;

    // Дойдя до начала списка, перейти к последнему изображению
    if(iCurFile < dirContent.indexOf(dirContent.first(), 0)) {
        iCurFile = dirContent.indexOf(dirContent.last(), 0);
    }

    // Загрузить изображение
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    loadImage(str);
}