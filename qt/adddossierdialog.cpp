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
    QStringList formations;
    std::vector<Formation> iterator = FM->iterator();

    for(auto it=iterator.begin(); it!=iterator.end(); it++) {
        formations<<it->getName();
    }

    ui->formationBox->addItems(formations);
    QStringList header;
    header << "Abbréviation" << "Nom";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void AddDossierDialog::createDossier() {
    Dossier d(ui->loginEdit->text());
    for(auto it=formations.begin(); it!=formations.end(); it++) {
        Formation f = FM->getItem(*it);
        d.addFormation(f);
    }
    DM->addItem(d);
    close();
}

void AddDossierDialog::formationAdded() {
    formations.push_back(ui->formationBox->currentText());
    ui->formationBox->removeItem(ui->formationBox->currentIndex());

    Formation f = FM->getItem(ui->formationBox->currentText());

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(f.getName()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(f.getLongName()));
}

AddDossierDialog::~AddDossierDialog()
{
    delete ui;
}