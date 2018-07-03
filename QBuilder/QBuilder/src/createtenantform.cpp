#include "createtenantform.h"
#include "ui_createtenantform.h"

#include <QPainter>

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(Table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    // region Country
    // Set relation between tables
    int countryIndex = model->fieldIndex("country");
    model->setRelation(countryIndex, QSqlRelation("location_country", "id", "country_name"));

    // New relation model for fTypeBox
    QSqlTableModel *countryModel = model->relationModel(countryIndex); // Relation index
    ui->countryBox->setModel(countryModel);
    ui->countryBox->setModelColumn(countryModel->fieldIndex("country_name"));
    // endregion Country

    // region City
    // Set relation between tables
    int cityIndex = model->fieldIndex("city");
    model->setRelation(cityIndex, QSqlRelation("location_city", "id", "city_name"));

    // New relation model for fTypeBox
    QSqlTableModel *cityModel = model->relationModel(cityIndex); // Relation index
    ui->cityBox->setModel(cityModel);
    ui->cityBox->setModelColumn(cityModel->fieldIndex("city_name"));
    // endregion City

    // View data in lineEdit with mapper
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->tenantCodeLine, 1);
    mapper->addMapping(ui->tenantNameLine, 2);
    mapper->addMapping(ui->emailLine, 3);
    mapper->addMapping(ui->phoneLine, 4);
    mapper->addMapping(ui->countryBox, countryIndex);   // Relation by index
    mapper->addMapping(ui->cityBox, cityIndex);   // Relation by index
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

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

void CreateTenantForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
