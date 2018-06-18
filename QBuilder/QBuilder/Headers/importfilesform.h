#ifndef IMPORTFILESFORM_H
#define IMPORTFILESFORM_H

#include <QWidget>

namespace Ui {
class ImportFilesForm;
}

class ImportFilesForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImportFilesForm(QWidget *parent = 0);
    ~ImportFilesForm();

private:
    Ui::ImportFilesForm *ui;

    void importFiles(); // Import files
};

#endif // IMPORTFILESFORM_H
