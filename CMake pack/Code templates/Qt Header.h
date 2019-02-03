#[[#ifndef]]# ${NAME}_H
#[[#define]]# ${NAME}_H

#[[#include]]# <${QT_CLASS}>

namespace Ui {
class ${NAME};
}

class ${NAME} : public ${QT_CLASS}
{
    Q_OBJECT

public:
    explicit ${NAME}(QWidget *parent = 0);
    ~${NAME}();

private:
    Ui::${NAME} *ui;
};

#[[#endif]]# //${NAME}_H
