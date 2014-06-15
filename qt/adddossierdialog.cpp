#include "adddossierdialog.h"
#include "ui_adddossierdialog.h"

#include "src/formation.hpp"
#include "src/dossier.hpp"

#define FM FormationManager::getInstance()
#define DM DossierManager::getInstance()

AddDossierDialog::AddDossierDialog(QWidget *parent)  :
    QDialog(parent), dossier(""),
    ui(new Ui::AddDossierDialog)
{
    ui->setupUi(this);

    ui->formationBox->addItems(FM->getItemNameList());

    QStringList header;
    header << "Abbréviation" << "Nom";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void AddDossierDialog::setDossier(const QString &name) {
    editionMode = true;
    dossier = DM->getItem(name);
    ui->loginEdit->setText(name);
    ui->loginEdit->setDisabled(true);
}


void AddDossierDialog::createDossier() {
    if (!editionMode) {
        dossier = Dossier();

    }

    dossier.setName(ui->loginEdit->text());
    dossier.resetFormations();

    for(auto it=formations.begin(); it!=formations.end(); it++) {
        Formation f = FM->getItem(*it);
        dossier.addFormation(f);
    }

    if (!editionMode) {
        DM->addItem(dossier);
    }

    close();
}

void AddDossierDialog::formationAdded() {
    QString formation = ui->formationBox->currentText();
    formations.push_back(formation);
    ui->formationBox->removeItem(ui->formationBox->currentIndex());

    Formation f = FM->getItem(formation);

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(f.getName()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(f.getLongName()));
}

AddDossierDialog::~AddDossierDialog()
{
    delete ui;
}
