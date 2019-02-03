#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    /* * * Слоты * * */ {
        // Открыть изображение
        connect(ui->openBtn, &QPushButton::clicked, this, [this] {
            emit openImg();
        });
        // Во весь экран
        connect(ui->fullScrBtn, &QPushButton::clicked, this, [this] {
            emit fullScreen();
        });
        // О программе
        connect(ui->aboutBtn, &QPushButton::clicked, this, [this] {
            emit aboutProgram();
        });
        // О Qt
        connect(ui->aboutQtBtn, &QPushButton::clicked, this, [this] {
            emit aboutQt();
        });
    }
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
