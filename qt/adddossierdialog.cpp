#include "adddossierdialog.h"
#include "ui_adddossierdialog.h"

#include "src/formation.hpp"
#include "src/dossier.hpp"
#include "addsemestredialog.h"

#include <QMessageBox>

#define FM FormationManager::getInstance()
#define DM DossierManager::getInstance()

//! Ouverture du Pop up création de dossier
AddDossierDialog::AddDossierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDossierDialog)
{
    ui->setupUi(this);

    ui->formationBox->addItems(FM->getItemNameList());

    QStringList header;
    header << "Abbréviation" << "Nom";

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList headerSemestre;
    header << "Semestre" << "Date";
    ui->tableSemestre->setColumnCount(2);
    ui->tableSemestre->setHorizontalHeaderLabels(headerSemestre);
    ui->tableSemestre->setRowCount(0);
    ui->tableSemestre->verticalHeader()->setVisible(false);
    ui->tableSemestre->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void AddDossierDialog::setDossier(const QString &name) {
    editionMode = true;
    dossier = DM->getItem(name);
    dossier.resetFormations();
    ui->loginEdit->setText(name);
    ui->loginEdit->setDisabled(true);
}

void AddDossierDialog::setDossier() {
    dossier = Dossier();
    editionMode = false;
}

void AddDossierDialog::semestreAdded() {
    if (dossier.getFormations().size() == 0) {
        QMessageBox error(this);
        error.setText("Veuillez ajouter une formation");
        error.exec();
        return;
    }

    AddSemestreDialog *dialog = new AddSemestreDialog(this, &dossier);
    dialog->exec();

    std::vector<Semestre> semestres = dossier.getSemestres();
    ui->tableSemestre->clearContents();
    ui->tableSemestre->setRowCount(0);

    for(auto it=semestres.begin(); it!=semestres.end(); it++) {
        ui->tableSemestre->setRowCount(ui->tableSemestre->rowCount() + 1);

        QTableWidgetItem *nomitem= new QTableWidgetItem(it->getName());
        nomitem->setFlags(nomitem->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *semitem= new QTableWidgetItem(it->getSemestre().representation);
        semitem->setFlags(semitem->flags() & ~Qt::ItemIsEditable);

        ui->tableSemestre->setItem(ui->tableSemestre->rowCount()-1, 0, nomitem);
        ui->tableSemestre->setItem(ui->tableSemestre->rowCount()-1, 1, semitem);
    }

    return;
}

//! Création d'un nouveau dossier
void AddDossierDialog::createDossier() {
    dossier.setName(ui->loginEdit->text());

    if (!editionMode) {
        DM->addItem(dossier);
    }

    close();
}

//! Ajout d'une formation au dossier (ex : TC, GI, SRI)
void AddDossierDialog::formationAdded() {
    QString formation = ui->formationBox->currentText();
    Formation f = FM->getItem(formation);
    dossier.addFormation(f);

    ui->formationBox->removeItem(ui->formationBox->currentIndex());



    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(f.getName()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(f.getLongName()));
}

AddDossierDialog::~AddDossierDialog()
{
    delete ui;
}
