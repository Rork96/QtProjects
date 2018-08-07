#include "CommandPrompt.h"
#include "ui_CommandPrompt.h"

CommandPrompt::CommandPrompt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommandPrompt)
{
    ui->setupUi(this);

    m_process = new QProcess(this);

    connect(m_process, &QProcess::readyReadStandardOutput, this, &CommandPrompt::setStdout);
    //connect()
    // connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(command()) );
}

CommandPrompt::~CommandPrompt()
{
    delete ui;
}

void CommandPrompt::setStdout()
{
    if(QSysInfo::productType() == "windows") {
        QTextCodec *codec = QTextCodec::codecForName("IBM 866");
        //ui->textEdit->append( codec->toUnicode(m_process->readAllStandardOutput() ) );
    }
    else {
        //ui->textEdit->append(m_process->readAllStandardOutput());
    }
}

void CommandPrompt::command()
{
    QString strCommand;
    if(QSysInfo::productType() == "windows") strCommand = "cmd /C ";
    //strCommand += ui->lineEdit->text();
    m_process->start(strCommand);
}
