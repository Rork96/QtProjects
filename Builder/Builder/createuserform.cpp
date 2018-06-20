#include "createuserform.h"
#include "ui_createuserform.h"

#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>

CreateUserForm::CreateUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateUserForm)
{
    ui->setupUi(this);    

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateUserForm::submitChanges);

    QList<QComboBox*> elements = {ui->backColorBox, ui->menuTextColorBox, ui->highlightColorBox, ui->borderColorBox, ui->bodyBackColorBox,
                                  ui->linkColorBox, ui->bodyTextColorBox, ui->bodyInfColorBox, ui->sectionColorBox, ui->sectionHeadColorBox,
                                  ui->sectionBackColorBox, ui->sectionColorBox_2, ui->sectionHeadColorBox_2, ui->sectionBackColorBox_2,
                                  ui->searchColorBox, ui->selectedSearchColorBox, ui->fieldColorBox, ui->fieldSelectedColorBox, ui->tabColorBox,
                                  ui->tabUnselectedColorBox, ui->messageColorBox, ui->messageBackColorBox, ui->chart_1_ColorBox, ui->chart_2_ColorBox,
                                  ui->chart_3_ColorBox, ui->chart_4_ColorBox};

    initComboBox(elements);   // Init comboboxes with colors

    connect(ui->avatarButton, &QPushButton::clicked, this, &CreateUserForm::openImage);
    connect(ui->bodyImgButton, &QPushButton::clicked, this, &CreateUserForm::openImage);
    connect(ui->menuImgButton, &QPushButton::clicked, this, &CreateUserForm::openImage);
}

CreateUserForm::~CreateUserForm()
{
    delete ui;
}

void CreateUserForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}

void CreateUserForm::openImage(/*QWidget *sender*/)
{
    // Open image

    QString fName = QFileDialog::getOpenFileName(this, "Choose files",
                           QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Supported files (*.png | *.jpg | *.jpeg);;"
                                                 "*.png;; *.jpg;; *.jpeg;; All files (*.*)");

    if(fName.isEmpty()) return;

    QPushButton *button = ((QPushButton *)sender());

    if (button == ui->avatarButton) {
        ui->avatarNameLabel->setText(QFileInfo(fName).fileName());
    }
    else if (button == ui->bodyImgButton) {
        ui->bodyImgNameLabel->setText(QFileInfo(fName).fileName());
    }
    else {
        ui->menuImgNameLabel->setText(QFileInfo(fName).fileName());
    }
}

void CreateUserForm::initComboBox(QList<QComboBox*> elements)
{
    // Init comboboxes with colors
    foreach (QComboBox *element, elements) {
        QStringList colorNames;
        colorNames = QColor::colorNames();

        element ->setFocusPolicy(Qt::NoFocus);
        int size = element ->style()->pixelMetric(QStyle::PM_SmallIconSize);
        QPixmap pixmap(size, size-5);

        int con = 0;
        foreach (const QString &colorName, colorNames) {
            element->addItem(colorName);                                // Color name
            pixmap.fill(QColor(colorName));

            QRect rBorder(0, 0, size-1, size-6);
            QPainter p(&pixmap);
            QPen pen(Qt::lightGray, 1, Qt::SolidLine);
            p.setPen(pen);
            p.drawRect(rBorder);

            element->setItemData(con, pixmap, Qt::DecorationRole);      // Color icon
            con = con + 1;
        }
    }
}
