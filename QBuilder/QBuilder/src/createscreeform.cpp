#include "createscreeform.h"
#include "ui_createscreeform.h"

#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include "basecombomodel.h"

CreateScreeForm::CreateScreeForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateScreeForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Tab text

    initData(Table);

    // Set relation between tables
    int scrIndex = model->fieldIndex("scr_name");
    model->setRelation(scrIndex, QSqlRelation("group_screen", "id", "s_text"));
    int libIndex = model->fieldIndex("library");
    model->setRelation(libIndex, QSqlRelation("templates", "id", "library_name"));

    model->select();

    // New relation model for groupNameBox
    QSqlTableModel *relModel = model->relationModel(scrIndex); // Relation index
    ui->scrNameBox->setModel(relModel);
    ui->scrNameBox->setModelColumn(relModel->fieldIndex("s_text"));

    // New relation model for menuNameBox
    QSqlTableModel *rModel = model->relationModel(libIndex); // Relation index
    ui->libraryBox->setModel(rModel);
    ui->libraryBox->setModelColumn(rModel->fieldIndex("library_name"));

    // View data with mapper
    // First not displayed
    mapper->addMapping(ui->scrNameBox, scrIndex);
    mapper->addMapping(ui->libraryBox, libIndex);
    mapper->addMapping(ui->tabTextLine, 4);
    mapper->addMapping(ui->descriptionEdit, 5);
    mapper->addMapping(ui->tabWeightSpinBox, 6);
    mapper->addMapping(ui->templateEdit, 7);
    mapper->addMapping(ui->desctopBox, 8);
    mapper->addMapping(ui->mobileBox, 9);
    mapper->addMapping(ui->webBox, 10);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    ui->templateEdit->setPlainText( "{\n"
                                    "  \"layout_type\": null,\n"
                                    "  \"search_configuration\": null,\n"
                                    "  \"search_custom_query\": null,\n"
                                    "  \"template_layout\": null,\n"
                                    "  \"screen_extensions\": {\n"
                                    "    \"add\": {\n"
                                    "      \"pre\": null,\n"
                                    "      \"post\": null\n"
                                    "    },\n"
                                    "    \"delete\": {\n"
                                    "      \"pre\": null,\n"
                                    "      \"post\": null\n"
                                    "    },\n"
                                    "    \"edit\": {\n"
                                    "      \"pre\": null,\n"
                                    "      \"post\": null\n"
                                    "    },\n"
                                    "    \"inquire\": {\n"
                                    "      \"pre\": null,\n"
                                    "      \"post\": null\n"
                                    "    },\n"
                                    "    \"execute\": {\n"
                                    "      \"pre\": null,\n"
                                    "      \"post\": null\n"
                                    "    },\n"
                                    "    \"executeFunction\": {\n"
                                    "      \"library\": null,\n"
                                    "      \"function\": null,\n"
                                    "      \"custom\": null\n"
                                    "    }\n"
                                    "  },\n"
                                    "  \"step_screen\": {\n"
                                    "    \"enable\": false,\n"
                                    "    \"icon\": null\n"
                                    "  },\n"
                                    "  \"alias_framework\": {\n"
                                    "    \"enable\": false,\n"
                                    "    \"transaction_request\": null\n"
                                    "  }\n"
                                    "}" );

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateScreeForm::submitChanges);

    // Tab text
    connect(ui->tabTextLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->tabTextLine->text().isEmpty());
    });
}

CreateScreeForm::~CreateScreeForm()
{
    delete ui;
}

void CreateScreeForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " + Record + " FROM" + Table +
            " WHERE '" + Record + "' = '%1' AND id != %2 )").arg(ui->tabTextLine->text()).
            arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Tab text is already exists"));
        return;
    }
    else {
        // Insert new data
        mapper->submit();
        model->submitAll();

        if (query.exec("SELECT menu_name FROM group_screen WHERE s_text = '" + ui->scrNameBox->currentText() + "'")) {
            while (query.next()) {
                int result = query.value(0).toInt();
                mapper->submit();
                model->submitAll();
                query.prepare("UPDATE " + Table + " SET m_name = ? WHERE id = ?");
                query.addBindValue(result); // m_name
                if (isEdit) {
                    // If existing record is editing, get id
                    query.addBindValue(model->record(mapper->currentIndex()).value("id").toInt());
                } else {
                    // get id of the last inserted row
                    query.addBindValue(query.lastInsertId().toInt());
                }
                query.exec();
            }
        }
    }
    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}
