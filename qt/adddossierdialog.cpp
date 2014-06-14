#include "adddossierdialog.h"
#include "ui_adddossierdialog.h"

#include "src/formation.hpp"
#include "src/dossier.hpp"

#define FM FormationManager::getInstance()
#define DM DossierManager::getInstance()

AddDossierDialog::AddDossierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDossierDialog)
{
    ui->setupUi(this);
    editionMode = false;

    dossier = NULL;

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

AddDossierDialog::AddDossierDialog(QWidget *parent, Dossier& d)  :
    QDialog(parent),
    ui(new Ui::AddDossierDialog)
{
    ui->setupUi(this);
    editionMode = true;
    dossier = d;

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

//! Création d'un nouveau dossier
void AddDossierDialog::createDossier() {
    Dossier &d;
    if (editionMode) {
        d = dossier;
        d.resetFormations();
    } else {
        d(ui->loginEdit->text());
    }

    for(auto it=formations.begin(); it!=formations.end(); it++) {
        Formation f = FM->getItem(*it);
        d.addFormation(f);
    }

    if (!editionMode) {
        DM->addItem(d);
    }

    close();
}

//! Ajout d'une formation au dossier (ex : TC, GI, SRI)
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
