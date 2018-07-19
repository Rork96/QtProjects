#[[#include]]# "${NAME}.h"
#[[#include]]# "ui_${NAME}.h"

${NAME}::${NAME}(QWidget *parent) :
    ${QT_CLASS}(parent),
    ui(new Ui::${NAME})
{
    ui->setupUi(this);
}

${NAME}::~${NAME}()
{
    delete ui;
}
