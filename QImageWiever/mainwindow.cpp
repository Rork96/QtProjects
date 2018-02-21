#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QScreen>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     /* * * Начальные настройки приложения * * */ {
        // Окно развернуто на весь экран
        setWindowState(Qt::WindowMaximized);

        // Цвер фона
        setStyleSheet("background-color: #EEEEF1;");

        // Установка QGraphicsView и QGraphicsScene
        // для отображения изображения
        gView = new QGraphicsView();
        setCentralWidget(gView);
        scene = new QGraphicsScene();
        gView->setScene(scene);
        // По центру
        gView->centerOn(0, 0);

        /* Прозрачная кнопка */
        QString styleButton=QString("QAbstractButton {background: rgba(255,255,255,100);}");

        rBtn = new QPushButton("", this);
        rBtn->setIcon(QPixmap(":/pict/left.png"));
        rBtn->setIconSize(QSize(50, 50));
        rBtn->setStyleSheet(styleButton);
        rBtn->setFlat(true);
        rBtn->setGeometry(20, geometry().width(), 60, 60);
        rBtn->setVisible(false);

        lBtn = new QPushButton("", this);
        lBtn->setIcon(QPixmap(":/pict/right.png"));
        lBtn->setIconSize(QSize(50, 50));
        lBtn->setStyleSheet(styleButton);
        lBtn->setFlat(true);
        lBtn->setGeometry(QApplication::screens().at(0)->geometry().width()-lBtn->width()/2-30, geometry().width(), 60, 60);
        lBtn->setVisible(false);
        /* ************************* */
    }

    /* * * Горячие клавиши приложения * * */ {
        // Открыть изображение
        openShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);

        // Сохранить изображение
        saveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

        // Увеличить изображение
        zoomInShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus), this);

        // Уеньшить изображение
        zoomOutShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), this);

        // Следующее изображение
        nextImageShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);

        // Предыдущее изображение
        prevImageShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);

        // Поворот в право на 90 град
        rotRightShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right), this);

        // Поворот в лево на 90 град
        rotLeftShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left), this);

        // О программе
        aboutAction = new QAction("О программе", this);
    }

    /* * * Слоты * * */ {
        // Открыть изображение
        connect(openShortcut, &QShortcut::activated, this, &MainWindow::openImage);

        // Соханить изображение
        connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveImage);

        // Увеличить
        connect(zoomInShortcut, &QShortcut::activated, this, [this] {
            gView->scale(SCALE_IN, SCALE_IN);
        });

        // Уменьшить
        connect(zoomOutShortcut, &QShortcut::activated, this, [this] {
            gView->scale(SCALE_OUT, SCALE_OUT);
        });

        // Следующее изображение
        connect(nextImageShortcut, &QShortcut::activated, this, &MainWindow::nextImage);
        connect(rBtn, &QPushButton::clicked, nextImageShortcut, &QShortcut::activated);

        // Предыдущее изображение
        connect(prevImageShortcut, &QShortcut::activated, this, &MainWindow::prevImage);
        connect(lBtn, &QPushButton::clicked, prevImageShortcut, &QShortcut::activated);

        // Поворот в право на 90 град
        connect(rotRightShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_RIGHT);
        });

        // Поворот в лево на 90 град
        connect(rotLeftShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_LEFT);
        });

        // О программе
        connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutProgram);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{
    /* * * Открыть изображение * * */

    QString fName = QFileDialog::getOpenFileName(this, "Открыть изображение",
                QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                            "Файлы изображений (*.jpg | *.jpeg | *.png | *.bmp)");

    if(fName.isEmpty()) return;

    // Получить все файлы директории
    QDir dir(QFileInfo(fName).absoluteDir());
    dirContent = dir.entryInfoList(QStringList() << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp",
                                                 QDir::Files | QDir::NoDotAndDotDot);

    // Сохранить индекс выбранного изображения
    iCurFile = dirContent.indexOf(QFileInfo(fName), 0);
    // Отобразить выбранное изображение
    loadImage(fName);
}

inline void MainWindow::loadImage(const QString& str)
{
    /* * * Загрузка изображения * * */

    // Добавить новый элемент на сцену
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem();
    scene->addItem(pixItem);

    // Получить все элементы в сцены
    QList<QGraphicsItem *> item = scene->items();

    // Если в сцене больше одного элемента, то
    // удалить предыдущий
    if(item.count() > 1) delete item.last();

    // Сравнить размеры клиентской области окна с размерами изображения
    if( (QPixmap(str).width() < geometry().width()) || (QPixmap(str).height() < geometry().height()) ) {
        // изображение в реальном размере
        gView->setSceneRect(0, 0, QPixmap(str).width(), QPixmap(str).height());
        gView->fitInView(pixItem, Qt::KeepAspectRatio);
        pixItem->setPixmap(QPixmap(str));
    }
    else {
        // вписать изображение в сцену (клиентскую область окна)
        pixItem->setPixmap(QPixmap(str));
        gView->setSceneRect(0, 0, geometry().width(), geometry().height());
        gView->fitInView(pixItem, Qt::KeepAspectRatio);
    }

    // Отобразить элемент
    pixItem->setVisible(true);

    // Имя файла в заголовке окна
    setWindowTitle("QImageWiever - " + QFileInfo(str).fileName());

    // Показать элементы управления
    showElements();
}

void MainWindow::saveImage()
{
    /* * * Сохранить изображение * * */

    if(iCurFile == -1) return; // Нет открытых изображений

    // Открытый файл
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    QFile f(str);

    // Имя и путь к новому файлу
    QString fName = QFileDialog::getSaveFileName(this, "Открыть изображение",
               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                           "Файлы изображений (*.jpg | *.jpeg |*.png | *.bmp)");

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
    /* * * Следующее изображение * * */

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
    /* * * Предыдущее изображение * * */

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

void MainWindow::aboutProgram()
{
    /* * * О программе * * */

    QString aboutText;
    aboutText = "          QImageWiever  v 1.0.0  \n\n";
    aboutText += "Автор  : \tmasterarrow\n\n";
    aboutText += "email  : \tmasterarrows@gmail.com\n\n";
    aboutText += "          Copyright © 2018\n";

    QMessageBox::about(this, "О программе", aboutText);
}

void MainWindow::showElements()
{
    // Показать элементы управления
    rBtn->setVisible(true);
    lBtn->setVisible(true);
}