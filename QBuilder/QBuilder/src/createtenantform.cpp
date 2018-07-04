#include "createtenantform.h"
#include "ui_createtenantform.h"

#include <QPainter>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

#include "basecombomodel.h"

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->tenantCodeLine, 1);
    mapper->addMapping(ui->tenantNameLine, 2);
    mapper->addMapping(ui->emailLine, 3);
    mapper->addMapping(ui->phoneLine, 4);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTenantForm::submitChanges);

    QList<QComboBox*> elements = {ui->backColorBox, ui->menuTextColorBox, ui->borderColorBox, ui->linkColorBox, ui->headBordColorBox,
                                 ui->headColorBox, ui->infoColorBox, ui->menuBackColorBox, ui->menuTextColorBox, ui->msgColorBox,
                                 ui->searchBordColorBox, ui->sectBackColorBox, ui->sectHeaderColorBox, ui->selectionColorBox,
                                 ui->tabSelectColorBox, ui->tabUnselectColorBox, ui->textColorBox, ui->sectHeaderBackBox,
                                 ui->selectedSearchBox, ui->fieldsBordColorBox, ui->selectedFieldBox, ui->msgBackBox, ui->fChatColorBox,
                                 ui->sChatColorBox, ui->thChatColorBox, ui->fourChatColorBox};

    initComboBox(elements);   // Init comboboxes with colors
}

CreateTenantForm::~CreateTenantForm()
{
    delete ui;
}

void CreateTenantForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    BaseComboModel *countryCModel = new BaseComboModel("country_name", "location_country", this, Table, "country");
    BaseComboModel *cityCModel = new BaseComboModel("city_name", "location_city", this, Table, "city");

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    countryCModel->saveToDB(ui->countryBox->currentIndex(), id);
    cityCModel->saveToDB(ui->cityBox->currentIndex(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateTenantForm::initComboBox(QList<QComboBox*> elements)
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

void CreateTenantForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    BaseComboModel *countryCModel = new BaseComboModel("country_name", "location_country", this, Table, "country");
    ui->countryBox->setModel(countryCModel);
    ui->countryBox->setCurrentIndex(countryCModel->getIndex(id));

    BaseComboModel *cityCModel = new BaseComboModel("city_name", "location_city", this, Table, "city");
    ui->cityBox->setModel(cityCModel);
    ui->cityBox->setCurrentIndex(cityCModel->getIndex(id));
}
