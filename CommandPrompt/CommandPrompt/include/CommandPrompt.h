#ifndef CommandPrompt_H
#define CommandPrompt_H

#include <QMainWindow>

namespace Ui
{
class CommandPrompt;
}

class CommandPrompt: public QMainWindow
{
    Q_OBJECT

public:
    explicit CommandPrompt(QWidget *parent = 0);
    ~CommandPrompt();

private:
    Ui::CommandPrompt *ui;
};

#endif //CommandPrompt_H
