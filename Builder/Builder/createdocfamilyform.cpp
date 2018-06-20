#include "createdocfamilyform.h"
#include "ui_createdocfamilyform.h"

CreateDocFamilyForm::CreateDocFamilyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocFamilyForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocFamilyForm::submitChanges);

    connect(ui->addCategoryButton, &QToolButton::clicked, this, &CreateDocFamilyForm::addCategory);
}

CreateDocFamilyForm::~CreateDocFamilyForm()
{
    delete ui;
}

void CreateDocFamilyForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDocFamilyForm::addCategory()
{
    // Add new category

    catL.append(new QLineEdit(ui->categoryLine));
    descrL.append(new QLineEdit(ui->descriptionLine));
    kp_1_L.append(new QLineEdit(ui->kp_1_Line));
    kp_2_L.append(new QLineEdit(ui->kp_2_Line));
    kp_3_L.append(new QLineEdit(ui->kp_3_Line));
    kp_4_L.append(new QLineEdit(ui->kp_4_Line));
    kp_5_L.append(new QLineEdit(ui->kp_5_Line));
    searchL.append(new QLineEdit(ui->searchTextLine));
    delBtn.append(new QToolButton());

    delBtn.last()->setVisible(true);
    delBtn.last()->setIcon(QIcon(":/res/clear.png"));

    connect(delBtn.last(), &QToolButton::clicked, this, &CreateDocFamilyForm::delCategory);

    ui->verticalLayout->addWidget(catL.last());
    ui->verticalLayout_2->addWidget(descrL.last());
    ui->verticalLayout_3->addWidget(kp_1_L.last());
    ui->verticalLayout_4->addWidget(kp_2_L.last());
    ui->verticalLayout_5->addWidget(kp_3_L.last());
    ui->verticalLayout_6->addWidget(kp_4_L.last());
    ui->verticalLayout_7->addWidget(kp_5_L.last());
    ui->verticalLayout_8->addWidget(searchL.last());
    ui->verticalLayout_9->addWidget(delBtn.last());
}

void CreateDocFamilyForm::delCategory()
{
    // Delete category

    int number = delBtn.indexOf((QToolButton *)sender());

    catL.at(number)->deleteLater();
    catL.remove(number);
    descrL.at(number)->deleteLater();
    descrL.remove(number);
    kp_1_L.at(number)->deleteLater();
    kp_1_L.remove(number);
    kp_2_L.at(number)->deleteLater();
    kp_2_L.remove(number);
    kp_3_L.at(number)->deleteLater();
    kp_3_L.remove(number);
    kp_4_L.at(number)->deleteLater();
    kp_4_L.remove(number);
    kp_5_L.at(number)->deleteLater();
    kp_5_L.remove(number);
    searchL.at(number)->deleteLater();
    searchL.remove(number);
    delBtn.at(number)->deleteLater();
    delBtn.remove(number);
}
