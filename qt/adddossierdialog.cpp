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
    headerSemestre << "Semestre" << "Date" << "UVs";
    ui->tableSemestre->setColumnCount(3);
    ui->tableSemestre->setHorizontalHeaderLabels(headerSemestre);
    ui->tableSemestre->setRowCount(0);
    ui->tableSemestre->verticalHeader()->setVisible(true);
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
    std::cout<<ranges.length()<<std::endl;
    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        std::cout<<it->bottomRow()<<" "<<it->topRow()<<std::endl;

        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableWidget->item(i, 0)->text();
            std::cout<<nom.toStdString()<<std::endl;
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

    std::cout<<ranges.length()<<std::endl;
    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableSemestre->item(i, 0)->text();
            dossier.removeSemestre(nom);
            dossier.removeEquivalence(nom);
        }
    }

    refresh();
}

void AddDossierDialog::refresh() {
    std::vector<Semestre> semestres = dossier.getSemestres();
    std::vector<Formation> formations = dossier.getFormations();
    std::vector<Equivalence> equivalences = dossier.getEquivalences();

    ui->tableSemestre->clearContents();
    ui->tableSemestre->setRowCount(semestres.size() + equivalences.size());
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(formations.size());

    int semestreOffset = 0;
    for(auto it=semestres.begin(); it!=semestres.end(); it++) {
        ui->tableSemestre->setItem(semestreOffset, 0, getUneditableItem(it->getName()));
        ui->tableSemestre->setItem(semestreOffset, 1, getUneditableItem(it->getSemestre().representation));
        ui->tableSemestre->setItem(semestreOffset, 2, getUneditableItem(it->getUvList().join(", ")));
        semestreOffset++;
    }
    for(auto it=equivalences.begin(); it!=equivalences.end(); it++) {
        ui->tableSemestre->setItem(semestreOffset, 0, getUneditableItem(it->getName()));
        ui->tableSemestre->setItem(semestreOffset, 1, getUneditableItem(it->getSemestre().representation));
        ui->tableSemestre->setItem(semestreOffset, 2, getUneditableItem(it->getCreditsList().join(", ")));
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

    if (!editionMode) {
        dossier.setName(ui->loginEdit->text());
        DM->addItem(dossier);
    } else {
        Dossier& concerned = DM->getItem(dossier.getName());
        concerned = dossier;
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
