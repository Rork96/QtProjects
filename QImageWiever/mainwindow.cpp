#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QPrinter>
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
        // Заголовок окна
        setWindowTitle("Wellcome to QImageViewer");

        // Установка QGraphicsView и QGraphicsScene
        // для отображения изображения
        gView = new QGraphicsView(this);
        setCentralWidget(gView);

        /* * * Прозрачные кнопки: предыдущее и следующеее изображение * * */
        QString styleButton=QString("QAbstractButton {background: rgba(255,255,255,100);}");

        prevBtn = new QPushButton("", this);
        prevBtn->setIcon(QPixmap(":/pict/left.png"));
        prevBtn->setIconSize(QSize(50, 50));
        prevBtn->setStyleSheet(styleButton);
        prevBtn->setFlat(true);
        prevBtn->setGeometry(20, QApplication::screens().at(0)->geometry().height()/2, 50, 50);
        prevBtn->setVisible(false);

        nextBtn = new QPushButton("", this);
        nextBtn->setIcon(QPixmap(":/pict/right.png"));
        nextBtn->setIconSize(QSize(50, 50));
        nextBtn->setStyleSheet(styleButton);
        nextBtn->setFlat(true);
        nextBtn->setGeometry(QApplication::screens().at(0)->geometry().width()- (nextBtn->geometry().width()/2) -20,
                             QApplication::screens().at(0)->geometry().height()/2, 50, 50);
        nextBtn->setVisible(false);

        /* * * Начальное окно приветствия * * */
        wellcomePage();
    }

    /* * * Горячие клавиши приложения * * */ {
        // Открыть изображение
        openShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);

        // Сохранить изображение
        saveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

        // Удалить изображение
        delShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);

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
        // Нажатие кнопки открытия изображения в диалоговом окне
        connect(infoDlg, &InfoDialog::openImg, this, &MainWindow::openImage);

        // Соханить изображение
        connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveImage);

        // Удалить изображение
        connect(delShortcut, &QShortcut::activated, this, &MainWindow::delImage);

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
        // Нажатие кнопки во весь экран в диалоговом окне
        connect(infoDlg, &InfoDialog::fullScreen, fullScrShortcut, &QShortcut::activated);

        // О программе
        connect(aboutShortcut, &QShortcut::activated, this, &MainWindow::aboutProgram);
        // Нажатие кнопки о программе в диалоговом окне
        connect(infoDlg, &InfoDialog::aboutProgram, this, &MainWindow::aboutProgram);

        // О Qt
        connect(aboutQtShortcut, &QShortcut::activated, this, &MainWindow::aboutQt);
        // Нажатие о Qt в диалоговом окне
        connect(infoDlg, &InfoDialog::aboutQt, this, &MainWindow::aboutQt);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wellcomePage()
{
    /* * * Начальное окно приветствия * * */

    QGraphicsScene *gScene = new QGraphicsScene(this);
    //Добавление на сцену диалогового окна с прозрачным фоном
    infoDlg = new InfoDialog(this);
    infoDlg->setAttribute(Qt::WA_TranslucentBackground);
    gScene->addWidget(infoDlg);
    // Добавить сцену в GraphicsView
    gView->setScene(gScene);
}

void MainWindow::openImage()
{
    /* * * Открыть изображение * * */

    QString fName = QFileDialog::getOpenFileName(this, "Открыть изображение",
                QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                            "Файлы изображений (*.jpg | *.jpeg | *.png | *.bmp)");

    if (fName.isEmpty())
        return; // Файл не выбран

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

    // Создать новую графическую сцену и PixmapItem
    QGraphicsScene *gScene = new QGraphicsScene(this);
    // Добавить элемент с изображением на сцену
    QGraphicsPixmapItem *pix = gScene->addPixmap(QPixmap(str));

    // Если размер изображения больше размера окна, то
    // масштабировть изображение под размер окна
    if (pix->boundingRect().width() > geometry().width()) {
        // По ширине
        // (0.002 - уменьшение для отсутствия полосы прокрутки)
        // Если отключить полосы прокрутки их придется вкл. при приближении
        pix->setScale( geometry().width() / (pix->boundingRect().width()*1.0) -0.002);
//        gView->fitInView(geometry(), Qt::KeepAspectRatio);
    } else if (pix->boundingRect().height() > geometry().height()) {
        // По высоте
        pix->setScale( geometry().height() / (pix->boundingRect().height()*1.0) -0.002);
//        gView->fitInView(geometry(), Qt::KeepAspectRatio);
    }

    // Получить все элементы GraphicsView
    QList<QGraphicsItem *> item = gView->items();

    // Если в GraphicsView больше одного элемента (сцены), то
    // удалить предыдущий
    if (item.count() > 1)
        delete item.last();

    // Установить новую сцену в GraphicsView
    gView->setScene(gScene);

    // Имя файла в заголовке окна
    setWindowTitle("QImageViewer - " + QFileInfo(str).fileName());

    // Показать элементы управления
    showElements(true);
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

void MainWindow::delImage()
{
    /* * * Удалить изображение * * */

    QString str = dirContent[dirContent.indexOf(dirContent.at(iCurFile), 0)].absoluteFilePath();
    QFile(str).remove();

    // Удалить путь к файлу со списка
    dirContent.removeAt(iCurFile);

    // проверить наличие изображений в папке
    if (dirContent.count() == 0) {
        // Обнулить счетчик
        iCurFile = 0;
        // Показать начальное окно приветствия
        wellcomePage();
        // Скрыть элементы управления
        showElements(false);
        return;
    }

    // Показать следующее изображение
    nextImage();
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

void MainWindow::showElements(const bool show)
{
    /* * * Показ элементов управления * * */

    prevBtn->setVisible(show);
    nextBtn->setVisible(show);
}

void MainWindow::printImage()
{
    /* * * Передварительный просмотр печати изображения * * */

    if (iCurFile == -1)
        return; // Нет открытых изображений

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