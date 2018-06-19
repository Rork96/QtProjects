#include "tableform.h"
#include "ui_tableform.h"

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);

    ui->builderCreateButton->setVisible(false);     // Hide "Create with builder" button
    ui->builderUpdateButton->setVisible(false);     // Hide "Update with builder" button
    // Hide widgets for search
    ui->searchLine->setVisible(false);
    ui->searchParamBox->setVisible(false);

    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::searchInDB); // Search

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
       emit createData(this->viewType); // Create new data
    });

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // Selected row in table
}

TableForm::~TableForm()
{
    delete ui;
}

void TableForm::loadDataFromDB()
{
    // Load data
}

void TableForm::searchInDB()
{
    // Show widgets for search
    ui->searchLine->setVisible(!ui->searchLine->isVisible());
    ui->searchParamBox->setVisible(!ui->searchParamBox->isVisible());
    ui->searchLine->clear();
    ui->searchParamBox->clear();

    // Interactive search in current database table
}

void TableForm::setViewType(Type type)
{
    this->viewType = type;

    if (type == Type::screens || type == Type::custom_query) {
        ui->builderCreateButton->setVisible(true);  // Show "Create with builder" button
        ui->builderUpdateButton->setVisible(true);  // Show "Update with builder" button

        connect(ui->builderCreateButton, &QToolButton::clicked, this, [this] {
            emit createDataWithBuilder(this->viewType);  // Create new data with builder
        });
    }

    loadDataFromDB();
}

void TableForm::deleteDatafromDB()
{
    // Delete current data from database
}
