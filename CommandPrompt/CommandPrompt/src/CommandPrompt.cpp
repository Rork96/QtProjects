#include "CommandPrompt.h"
#include "ui_CommandPrompt.h"

CommandPrompt::CommandPrompt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommandPrompt)
{
    ui->setupUi(this);
}

CommandPrompt::~CommandPrompt()
{
    delete ui;
}
