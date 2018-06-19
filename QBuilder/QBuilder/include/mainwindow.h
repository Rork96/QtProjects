#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginform.h"
#include "tableform.h"
#include "creategroupform.h"
#include "createuserform.h"
#include "createtenantform.h"
#include "createlogoform.h"
#include "createsecurityfilterform.h"
#include "createmenuform.h"
#include "creategroupscreenform.h"
#include "createscreeform.h"
#include "createdocfamilyform.h"
#include "createdocgroupsform.h"
#include "createlistform.h"
#include "createtemplatesform.h"
#include "createdatasourceform.h"
#include "createextfuncform.h"
#include "createserverform.h"
#include "createquestionform.h"
#include "createqueryform.h"

#include "importfilesform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    LoginForm *loginForm;
    TableForm *mainForm;
    CreateGroupForm *groupForm;
    ImportFilesForm *importForm;
    CreateUserForm *userForm;
    CreateTenantForm *tenantForm;
    CreateLogoForm *logoForm;
    CreateSecurityFilterForm *securityFilterForm;
    CreateMenuForm *menuForm;
    CreateGroupScreenForm *groupScreenForm;
    CreateScreeForm *screenForm;
    CreateDocFamilyForm *docFamilyForm;
    CreateDocGroupsForm *docGroupsForm;
    CreateListForm *listForm;
    CreateTemplatesForm *templatesForm;
    CreateDataSourceForm *dataSourceForm;
    CreateExtFuncForm *extFuncForm;
    CreateServerForm *serverForm;
    CreateQuestionForm *questionForm;
    CreateQueryForm *queryForm;

    void initUI();                                          // Hide main menu and show login screen
    void login();                                           // Login
    void setMainView(TableForm::Type type);                // Set view type
    void createView(TableForm::Type type);                 // Create view in dependency of needed view type
    void createViewWithBuilder(TableForm::Type type);     // Create view with builder
};

#endif // MAINWINDOW_H
