#include "changesemestredialog.h"
#include "ui_changesemestredialog.h"
#include "src/uvmanager.hpp"

#define UVM UvManager::getInstance()

ChangeSemestreDialog::ChangeSemestreDialog(QWidget *parent, QString u) :
    QDialog(parent),
    ui(new Ui::ChangeSemestreDialog), uv(u)
{
    ui->setupUi(this);
    this->setWindowTitle("Ouverture de l'UV");
    Uv concerned = UVM->getItem(uv);
    ui->printemps->setChecked(concerned.getOuverturePrintemps());
    ui->automne->setChecked(concerned.getOuvertureAutomne());
    connect(this, SIGNAL(accepted()), this, SLOT(closing()));
}

ChangeSemestreDialog::~ChangeSemestreDialog() {
    delete ui;
}


void ChangeSemestreDialog::closing() {
    Uv &concerned = UVM->getItem(uv);
    concerned.setOuvertureAutomne(ui->automne->isChecked());
    concerned.setOuverturePrintemps(ui->printemps->isChecked());
}
