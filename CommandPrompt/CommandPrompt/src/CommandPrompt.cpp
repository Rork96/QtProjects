#include "CommandPrompt.h"
#include "ui_CommandPrompt.h"

CommandPrompt::CommandPrompt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommandPrompt)
{
    ui->setupUi(this);

    m_edit = new PlaineEdit(this);
    setCentralWidget(m_edit);
}

CommandPrompt::~CommandPrompt()
{
    delete ui;
}
