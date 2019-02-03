#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPrinter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Размер окна
    resize(800, 600);

    // Отмена предыдущего действия
    retShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);

    /* Настройка интерфейса */ {
        // Установить графическую сцену
        scene = new PaintScene();
        ui->graphicsView->setScene(scene);
        // Скрыть панель применения изменений
        ui->applyToolBar->setVisible(false);
    }

    /* Слоты */ {
        // Сохранить
        connect(ui->actionSaveToFile, &QAction::triggered, ui->actionSave,
                &QAction::triggered);
        // Увеличить
        connect(ui->actionZoomIn, &QAction::triggered, this, [this] {
            ui->graphicsView->scale(SCALE_IN, SCALE_IN);
        });
        // Уменьшить
        connect(ui->actionZoomOut, &QAction::triggered, this, [this] {
            ui->graphicsView->scale(SCALE_OUT, SCALE_OUT);
        });
        connect(ui->actionSave, &QAction::triggered, this,
                &MainWindow::saveScrean);

        // Отмена предыдущего действия
        connect(retShortcut, &QShortcut::activated, scene,
                &PaintScene::removePrevItem);
    }

    // Показать иконку в трее
    showTrayIcon();

#ifdef Q_OS_WIN
    // Регистрация HotKey "CTRL+PrintScreen"
    // Системный идентификатор окна виджета, который будет обрабатывать HotKey
    RegisterHotKey((HWND)MainWindow::winId(),
                       100,                     // идентификатор HotKey
                       MOD_CONTROL,             // модификатор
                       VK_SNAPSHOT);            // горячая клавиша для HotKey
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printScrean()
{
    // Снимок экрана
    QScreen *screen = QApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);

    // Показать изображение
    scene->setPixmap(pixmap);
}

void MainWindow::saveScrean()
{
    // Сохранить снимок экрана

    QString fName = QFileDialog::getSaveFileName(this, "Сохранить изображение",
                QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Файлы изображений (*.png *)");

    if(fName.isEmpty()) return;

#ifdef Q_OS_LINUX
    fName.append(".pdf");
#endif

    QImage image(scene->width(), scene->height(),
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter;
    painter.begin(&image);
    scene->render(&painter);
    painter.end();
    image.save(fName);

    // Скрыть окно
    hide();
}

void MainWindow::showTrayIcon()
{
    // Показ иконки в трее

    // Создать экземпляр класса и задать его свойства
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("QScreener");
    QIcon trayImage(":/pict/QScreener.png");
    trayIcon->setIcon(trayImage);
    QMenu *trayIconMenu = new QMenu(this);
    QAction *close = new QAction("Выход из QScreener", this);

    connect(close, &QAction::triggered, this, &MainWindow::close);

    trayIconMenu->addAction(close);
    trayIcon->setContextMenu(trayIconMenu);

    // Вывести значок в трей
    trayIcon->show();
}

void MainWindow::changeEvent(QEvent *event)
{
    // Перехват сворачивания приложения - замена на сворачивание в трей
    QMainWindow::changeEvent(event);
    // При изменении состояния окна
    if (event -> type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            this->hide();   // Свернуть в трей
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Закрытие окна
    if (isHidden()) {
        event->accept();    // Если скрыто в трее - закрыть
    }
    else {
        hide();             // Иначе свернуть в трей
        event->ignore();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    // О программе

    QString aboutText;
    aboutText = "          QScreener  v 1.0.0  \n\n";
    aboutText += "Автор  : \tmasterarrow\n\n";
    aboutText += "email  : \tmasterarrow@mail.ru\n\n";
    aboutText += "          Copyright © 2017\n";

    QMessageBox::about(this, "О программе", aboutText);
}

void MainWindow::on_actionDarkColor_triggered()
{
    // Черный цвет
    scene->setColor(Qt::black);

    ui->actionBlooColor->setChecked(false);
    ui->actionDarkColor->setChecked(true);
    ui->actionGreenColor->setChecked(false);
    ui->actionRedColor->setChecked(false);
    ui->actionWhiteColor->setChecked(false);
    ui->actionYellowColor->setChecked(false);
}

void MainWindow::on_actionWhiteColor_triggered()
{
    // Белый цвет
    scene->setColor(Qt::white);

    ui->actionBlooColor->setChecked(false);
    ui->actionDarkColor->setChecked(false);
    ui->actionGreenColor->setChecked(false);
    ui->actionRedColor->setChecked(false);
    ui->actionWhiteColor->setChecked(true);
    ui->actionYellowColor->setChecked(false);
}

void MainWindow::on_actionRedColor_triggered()
{
    // Красный цвет
    scene->setColor(Qt::red);

    ui->actionBlooColor->setChecked(false);
    ui->actionDarkColor->setChecked(false);
    ui->actionGreenColor->setChecked(false);
    ui->actionRedColor->setChecked(true);
    ui->actionWhiteColor->setChecked(false);
    ui->actionYellowColor->setChecked(false);
}

void MainWindow::on_actionGreenColor_triggered()
{
    // Зеленый цвет
    scene->setColor(Qt::green);

    ui->actionBlooColor->setChecked(false);
    ui->actionDarkColor->setChecked(false);
    ui->actionGreenColor->setChecked(true);
    ui->actionRedColor->setChecked(false);
    ui->actionWhiteColor->setChecked(false);
    ui->actionYellowColor->setChecked(false);
}

void MainWindow::on_actionBlooColor_triggered()
{
    // Голубой цвет
    scene->setColor(Qt::blue);

    ui->actionBlooColor->setChecked(true);
    ui->actionDarkColor->setChecked(false);
    ui->actionGreenColor->setChecked(false);
    ui->actionRedColor->setChecked(false);
    ui->actionWhiteColor->setChecked(false);
    ui->actionYellowColor->setChecked(false);
}

void MainWindow::on_actionYellowColor_triggered()
{
    // Желтый цвет
    scene->setColor(Qt::yellow);

    ui->actionBlooColor->setChecked(false);
    ui->actionDarkColor->setChecked(false);
    ui->actionGreenColor->setChecked(false);
    ui->actionRedColor->setChecked(false);
    ui->actionWhiteColor->setChecked(false);
    ui->actionYellowColor->setChecked(true);
}

void MainWindow::on_actionPen_triggered()
{
    // Рисование маркером
    scene->drawElement = PaintScene::pen;

    ui->actionPen->setChecked(true);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionLine_triggered()
{
    // Рисование линии
    scene->drawElement = PaintScene::line;

    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(true);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionElipse_triggered()
{
    // Рисование элипса
    scene->drawElement = PaintScene::elipse;

    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(true);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionRectangle_triggered()
{
    // Рисование прямоугольника
    scene->drawElement = PaintScene::rectangle;

    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(true);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionText_triggered()
{
    // Рисование текста
    scene->drawElement = PaintScene::text;

    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(true);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionCut_triggered()
{
    // Обрезать изображение
    scene->drawElement = PaintScene::none;
    scene->setResizing(true);

    // Показать панель применения изменений
    ui->applyToolBar->setVisible(true);

    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(true);
}

void MainWindow::on_actionApply_triggered()
{
    // Применить изменения
    scene->setResizing(false);
    // Получить обрезанное изображение и
    // установить его на сцену
    scene->setPixmap(scene->Resize());

    // Скрыть панель применения изменений
    ui->applyToolBar->setVisible(false);

    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionCancel_triggered()
{
    // Отменить изменения
    scene->setResizing(false);
    scene->removePrevItem();

    // Скрыть панель применения изменений
    ui->applyToolBar->setVisible(false);

    ui->actionCut->setChecked(false);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    // Метод для обработки native событий от ОС в Qt

#ifdef Q_OS_WIN
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    // Преобразовать указатель message в MSG WinAPI
    MSG* msg = reinterpret_cast<MSG*>(message);

    // Если сообщение является HotKey, то
    if(msg->message == WM_HOTKEY) {
        // проверить идентификатор HotKey
        if(msg->wParam == 100) {
            // Сделать скриншот
            printScrean();
            show();
            return true;
        }
    }
    return false;
#endif
}

void MainWindow::on_actionCursor_triggered()
{
    // Курсор
    scene->drawElement = PaintScene::none;

    ui->actionCursor->setChecked(true);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionCut->setChecked(false);
    ui->actionElipse->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionText->setChecked(false);
    ui->actionCut->setChecked(false);
}

void MainWindow::on_actionPrint_triggered()
{
    // Печать скриншота

#ifndef QT_NO_PRINTER
    // Принтер
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);

    // Диалог предварительного просмотра
    QPrintPreviewDialog *dlg = new QPrintPreviewDialog(&printer, this);

    // Печать
    connect(dlg, &QPrintPreviewDialog::paintRequested, this,
            &MainWindow::print);

    dlg->setWindowTitle("Передварительный просмотр");
    dlg->exec();
#endif
}

void MainWindow::print(QPrinter *printer)
{
    // Печать

    // Записать содержимое scene в image
    QImage image(scene->width(), scene->height(),
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter;
    painter.begin(&image);
    scene->render(&painter);
    painter.end();

    // Передать в QPixmap
    QPixmap pix;
    pix.convertFromImage(image);

#ifndef QT_NO_PRINTER
    QPainter paint;
    // Масштабирование изображения под лист
    pix = pix.scaled(printer->pageRect().width(),
                     printer->pageRect().height(), Qt::KeepAspectRatio);
    // Вывод на печать
    paint.begin(printer);
    paint.drawPixmap(0, 0, pix);
    paint.end();
#endif
}

