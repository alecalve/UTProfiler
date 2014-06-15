#include "adduvdialog.h"
#include "ui_adduvdialog.h"

#include "changecreditsdialog.h"
#include "changesemestredialog.h"
#include "src/uvmanager.hpp"

#define UVM UvManager::getInstance()

//! Ouverture du Pop up d'ajout d'UV
AddUVDialog::AddUVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUVDialog)
{
    ui->setupUi(this);
}

//! Fermeture du pop up et création de l'UV par l'obtention d'un code et d'une description
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
