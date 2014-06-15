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
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList headerSemestre;
    header << "Semestre" << "Date";
    ui->tableSemestre->setColumnCount(2);
    ui->tableSemestre->setHorizontalHeaderLabels(headerSemestre);
    ui->tableSemestre->setRowCount(0);
    ui->tableSemestre->verticalHeader()->setVisible(true);
    ui->tableSemestre->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void AddDossierDialog::setDossier(const QString &name) {
    editionMode = true;
    dossier = DM->getItem(name);

    ui->loginEdit->setText(name);
    ui->loginEdit->setDisabled(true);
    refresh();
}

void AddDossierDialog::formationRemoved() {
    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();

    if (ranges.length() == 0) {
        QMessageBox error(this);
        error.setText("Aucune ligne sélectionnée");
        error.exec();
        return;
    }

    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableWidget->item(i, 0)->text();
            try {
                dossier.removeFormation(nom);
            } catch (const Exception &e) {
                QMessageBox error(this);
                error.setText(e.getinfo());
                error.exec();
                return;
            }
        }
    }

    refresh();
}

void AddDossierDialog::semestreRemoved() {
    QList<QTableWidgetSelectionRange> ranges = ui->tableSemestre->selectedRanges();

    if (ranges.length() == 0) {
        QMessageBox error(this);
        error.setText("Aucune ligne sélectionnée");
        error.exec();
        return;
    }

    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableWidget->item(i, 0)->text();
            try {
                dossier.removeSemestre(nom);
            } catch (const Exception &e) {
                QMessageBox error(this);
                error.setText(e.getinfo());
                error.exec();
                return;
            }
        }
    }

    refresh();
}

void AddDossierDialog::refresh() {
    std::vector<Semestre> semestres = dossier.getSemestres();
    std::vector<Formation> formations = dossier.getFormations();

    ui->tableSemestre->clearContents();
    ui->tableSemestre->setRowCount(semestres.size());
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(formations.size());

    int semestreOffset = 0;
    for(auto it=semestres.begin(); it!=semestres.end(); it++) {
        ui->tableSemestre->setItem(semestreOffset, 0, getUneditableItem(it->getName()));
        ui->tableSemestre->setItem(semestreOffset, 1, getUneditableItem(it->getSemestre().representation));
        semestreOffset++;
    }

    int formationOffset = 0;
    for(auto it=formations.begin(); it!=formations.end(); it++) {
        ui->tableWidget->setItem(formationOffset, 0, getUneditableItem(it->getName()));
        ui->tableWidget->setItem(formationOffset, 1, getUneditableItem(it->getLongName()));
        formationOffset++;
    }


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

    refresh();
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
    refresh();
}

AddDossierDialog::~AddDossierDialog()
{
    delete ui;
}
