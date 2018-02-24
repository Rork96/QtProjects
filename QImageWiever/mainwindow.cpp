#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QScreen>
#include <QPrinter>
#include <QPushButton>
#include <QGraphicsPixmapItem>

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
        //scene = new ImageScene();
        //gView->setScene(scene);
        // Зафиксировать размер сцены
        // (15 - сдвиг в лево, 35 - уменьшение по высоте)
        //scene->setSceneRect(15, 0, geometry().width()*2, geometry().height()*2-35);

        /* * * Прозрачные кнопки: предыдущее и следующеее изображение * * */
        QString styleButton=QString("QAbstractButton {background: rgba(255,255,255,100);}");

        prevBtn = new QPushButton("", this);
        prevBtn->setIcon(QPixmap(":/pict/left.png"));
        prevBtn->setIconSize(QSize(50, 50));
        prevBtn->setStyleSheet(styleButton);
        prevBtn->setFlat(true);
        prevBtn->setGeometry(20, geometry().width(), 60, 60);
        prevBtn->setVisible(false);

        nextBtn = new QPushButton("", this);
        nextBtn->setIcon(QPixmap(":/pict/right.png"));
        nextBtn->setIconSize(QSize(50, 50));
        nextBtn->setStyleSheet(styleButton);
        nextBtn->setFlat(true);
        nextBtn->setGeometry(QApplication::screens().at(0)->geometry().width()-nextBtn->width()/2-30,
                          geometry().width(), 60, 60);
        nextBtn->setVisible(false);


        // Добавление на сцену диалогового окна :)
        QGraphicsScene *gScene = new QGraphicsScene();
        QPushButton *openButton = new QPushButton("Open");
        QPushButton *aboutButton = new QPushButton("About");
        QPushButton *aboutQtButton = new QPushButton("About Qt");
        QHBoxLayout *l = new QHBoxLayout();
        l->addWidget(openButton);
        QSpacerItem *i = new QSpacerItem(100, 50);
        l->addSpacerItem(i);
        l->addWidget(aboutButton);
        l->addSpacerItem(i);
        l->addWidget(aboutQtButton);
        QDialog * d = new QDialog();
        d->setGeometry(0, 0, 500, 100);
        d->setAttribute(Qt::WA_TranslucentBackground);
        d->setLayout(l);
        gScene->addWidget(d);

        connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage);
        connect(aboutButton, &QPushButton::clicked, this, &MainWindow::aboutProgram);
        connect(aboutQtButton, &QPushButton::clicked, this, &MainWindow::aboutQt);

        gView->setScene(gScene);
    }

    /* * * Горячие клавиши приложения * * */ {
        // Открыть изображение
        openShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);

        // Сохранить изображение
        saveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

        // Печать изображения
        printShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this);

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

        // Во весь экран
        fullScrShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);

        // О программе
        aboutShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);

        // О Qt
        aboutQtShortcut = new QShortcut(QKeySequence(Qt::Key_F2), this);
    }

    /* * * Слоты * * */ {
        // Открыть изображение
        connect(openShortcut, &QShortcut::activated, this, &MainWindow::openImage);

        // Соханить изображение
        connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveImage);

        // Печать изображения
        connect(printShortcut, &QShortcut::activated, this, &MainWindow::printImage);

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
        connect(nextBtn, &QPushButton::clicked, nextImageShortcut, &QShortcut::activated);

        // Предыдущее изображение
        connect(prevImageShortcut, &QShortcut::activated, this, &MainWindow::prevImage);
        connect(prevBtn, &QPushButton::clicked, prevImageShortcut, &QShortcut::activated);

        // Поворот в право на 90 град
        connect(rotRightShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_RIGHT);
        });

        // Поворот в лево на 90 град
        connect(rotLeftShortcut, &QShortcut::activated, this, [this] {
            gView->rotate(ROT_LEFT);
        });

        // Во весь экран
        connect(fullScrShortcut, &QShortcut::activated, this, [this] {
            if (isFullScreen()) {
                setWindowState(Qt::WindowMaximized);
            } else {
                showFullScreen();
            }
        });

        // О программе
        connect(aboutShortcut, &QShortcut::activated, this, &MainWindow::aboutProgram);

        // О Qt
        connect(aboutQtShortcut, &QShortcut::activated, this, &MainWindow::aboutQt);
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

    if (fName.isEmpty())
        return;

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
/*
    // Добавить новый элемент на сцену
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem();
    scene->addItem(pixItem);

    // Получить все элементы в сцены
    QList<QGraphicsItem *> item = scene->items();

    // Если в сцене больше одного элемента, то
    // удалить предыдущий
    if (item.count() > 1)
        delete item.last();

    // Изображение в реальном размере
    gView->setSceneRect(0, 0, QPixmap(str).width(), QPixmap(str).height());
    gView->fitInView(pixItem, Qt::KeepAspectRatio);
    pixItem->setPixmap(QPixmap(str));*/

    /*
    // Сравнить размеры клиентской области окна с размерами изображения
    if ( (QPixmap(str).width() < geometry().width()) | (QPixmap(str).height() < geometry().height()) ) {
        // изображение в реальном размере
        gView->setSceneRect(0, 0, QPixmap(str).width(), QPixmap(str).height());
        gView->fitInView(pixItem, Qt::KeepAspectRatio);
        pixItem->setPixmap(QPixmap(str));
    } else { // Здесь ошибка
        // вписать изображение в сцену (клиентскую область окна)
        pixItem->setPixmap(QPixmap(str));
        gView->setSceneRect(0, 0, geometry().width(), geometry().height());
        gView->fitInView(pixItem, Qt::KeepAspectRatio);
    }*/

//    scene->clear();
//    scene->addPixmap(QPixmap(str));
    //scene->setPixmap(QPixmap(str));

    QPixmap pixmap(str);

    // Создать новую графическую сцену и PixmapItem
    QGraphicsScene *gScene = new QGraphicsScene();
//    QGraphicsPixmapItem *pix = new QGraphicsPixmapItem(pixmap);
    // Добавить элемент с изображением на сцену
    QGraphicsPixmapItem *pix = gScene->addPixmap(pixmap);

    // Если размер изображения больше размера окна, то
    // масштабировть изображение под размер окна
    if (pixmap.width() > geometry().width()) {
        pix->setScale(pixmap.width()/geometry().width());
//        pixmap.scaled(pixmap.width()/geometry().width(), pixmap.height()/geometry().height(),
//                      Qt::KeepAspectRatio);
    } else if (pixmap.height() > geometry().height()) {
        pix->setScale(pixmap.height()/geometry().height());
//        pixmap.scaled(pixmap.width()/geometry().width(), pixmap.height()/geometry().height(),
//                      Qt::KeepAspectRatio);
    }

    // Добавить элемент с изображением на сцену
//    gScene->addItem(pix);

    // Получить все элементы GraphicsView
    QList<QGraphicsItem *> item = gView->items();

    // Если в GraphicsView больше одного элемента (сцены), то
    // удалить предыдущий
    if (item.count() > 1)
        delete item.last();

    // Установить новую сцену в GraphicsView
    gView->setScene(gScene);

    gView->fitInView(0, 0, geometry().width(), geometry().height(), Qt::KeepAspectRatio);

    // Имя файла в заголовке окна
    setWindowTitle("QImageWiever - " + QFileInfo(str).fileName());

    // Показать элементы управления
    showElements();
}

void MainWindow::saveImage()
{
    /* * * Сохранить изображение * * */

    if (iCurFile == -1)
        return; // Нет открытых изображений

    // Открытый файл
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    QFile f(str);

    // Имя и путь к новому файлу
    QString fName = QFileDialog::getSaveFileName(this, "Открыть изображение",
               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                           "Файлы изображений (*.jpg | *.jpeg |*.png | *.bmp)");

    if (fName.isEmpty())
        return;

    // Добавить расширение если его нет
#ifdef Q_OS_LINUX
    if (QFileInfo(fName).suffix() == "")
        fName += ".jpg";
#endif

    // Сохранить изображение
    f.copy(fName);
}

void MainWindow::nextImage()
{
    /* * * Следующее изображение * * */

    if (iCurFile == -1)
        return; // Нет открытых изображений

    iCurFile++;

    // Дойдя до окнца списка, перейти к первоу изображению
    if (iCurFile > dirContent.indexOf(dirContent.last(), 0)) {
        iCurFile = dirContent.indexOf(dirContent.first(), 0);
    }

    // Загрузить изображение
    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    loadImage(str);
}

void MainWindow::prevImage()
{
    /* * * Предыдущее изображение * * */

    if (iCurFile == -1)
        return; // Нет открытых изображений

    iCurFile--;

    // Дойдя до начала списка, перейти к последнему изображению
    if (iCurFile < dirContent.indexOf(dirContent.first(), 0)) {
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
    /* * * Показать элементы управления * * */

    prevBtn->setVisible(true);
    nextBtn->setVisible(true);
}

void MainWindow::printImage()
{
    /* * * Передварительный просмотр печати изображения * * */

#ifndef QT_NO_PRINTER
    // Принтер
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);

    // Диалог предварительного просмотра
    QPrintPreviewDialog *dlg = new QPrintPreviewDialog(&printer, this);

    // Печать
    connect(dlg, &QPrintPreviewDialog::paintRequested, this, &MainWindow::print);

    dlg->setWindowTitle("Передварительный просмотр");
    dlg->exec();
#endif
}

void MainWindow::print(QPrinter *printer)
{
    /* * * Печать * * */

    QPixmap pix(dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath());

#ifndef QT_NO_PRINTER
    QPainter paint;
    // Масштабирование изображения под лист
    pix = pix.scaled(printer->pageRect().width(), printer->pageRect().height(), Qt::KeepAspectRatio);
    // Вывод на печать
    paint.begin(printer);
    paint.drawPixmap(0, 0, pix);
    paint.end();
#endif
}

void MainWindow::aboutQt()
{
    /* * * О Qt * * */

    QMessageBox::aboutQt(this, "About Qt");
}