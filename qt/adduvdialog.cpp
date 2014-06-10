#include "adduvdialog.h"
#include "ui_adduvdialog.h"

#include "changecreditsdialog.h"
#include "changesemestredialog.h"
#include "src/uvmanager.hpp"

#define UVM UvManager::getInstance()

AddUVDialog::AddUVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUVDialog)
{
    ui->setupUi(this);
}

void AddUVDialog::endCreationProcess() {

    close();

    QString code, descr;
    code = ui->codeEdit->text();
    descr = ui->descriptionEdit->text();
    Uv uv(code, descr);
    UVM->addItem(uv);

    ChangeCreditsDialog *credits = new ChangeCreditsDialog(this, code);
    credits->exec();
    delete credits;

    ChangeSemestreDialog *semestre = new ChangeSemestreDialog(this, code);
    semestre->exec();
    delete semestre;
}

AddUVDialog::~AddUVDialog() {
    delete ui;
}
