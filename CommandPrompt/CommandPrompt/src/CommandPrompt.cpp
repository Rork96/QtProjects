#include "CommandPrompt.h"
#include "ui_CommandPrompt.h"

CommandPrompt::CommandPrompt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommandPrompt)
{
    ui->setupUi(this);

    m_process = new QProcess(this);

    m_edit = new PlaineEdit(this);
    m_edit->setPlaceholderText("C:> ");
    setCentralWidget(m_edit);

    connect(m_process, &QProcess::readyReadStandardOutput, this, &CommandPrompt::setStdout);
    connect(m_edit, &PlaineEdit::returnPressed, this, &CommandPrompt::command);
}

CommandPrompt::~CommandPrompt()
{
    delete ui;
}

void CommandPrompt::setStdout()
{
    if(QSysInfo::productType() == "windows") {
        QTextCodec *codec = QTextCodec::codecForName("IBM 866");
        m_edit->setPlainText(m_edit->toPlainText() + codec->toUnicode(m_process->readAllStandardOutput()));
    }
    else {
        m_edit->setPlainText(m_process->readAllStandardOutput());
    }
    m_edit->textCursor().setPosition(m_edit->textCursor().position());
}

void CommandPrompt::command()
{
    QString strCommand;
    if(QSysInfo::productType() == "windows") strCommand = "cmd /C ";
    strCommand += m_edit->getLine();
    m_process->start(strCommand);
}
