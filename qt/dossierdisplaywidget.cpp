#include "dossierdisplaywidget.h"
#include "ui_displaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "src/dossier.hpp"
#include "src/formation.hpp"
#include "src/exceptions.hpp"
#include "adddossierdialog.h"

#define DM DossierManager::getInstance()
#define NBCOLS 3
#define NOM_COL 0
#define FORM_COL 1
#define SEM_COL 2


//! Onglet de gestion des dossiers etudiants
DossierDisplayWidget::DossierDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Login"<<"Formations suivies"<<"Semestres ajoutés";
    ui->searchOptions->addItems(cols);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

DossierDisplayWidget::~DossierDisplayWidget() {
    QString login = ui->tableWidget->item(NOM_COL, ui->tableWidget->currentRow())->text();
    Dossier d = DM->getItem(login);
}

void DossierDisplayWidget::modify() {
    Dossier d = DM->getItem(ui->tableWidget->item(ui->tableWidget->currentRow(), NOM_COL)->text());

    AddDossierDialog *dialog = new AddDossierDialog(this);
    dialog->setDossier(d.getName());
    dialog->exec();
    delete dialog;

    refresh();
}

void DossierDisplayWidget::add() {
    AddDossierDialog *dialog = new AddDossierDialog(this);
    dialog->exec();
    delete dialog;

    refresh();

}

void DossierDisplayWidget::del() {
    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();

    if (ranges.length() == 0) {
        QMessageBox error(this);
        error.setText("Aucune ligne sélectionnée");
        error.exec();
        return;
    }

    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableWidget->itemAt(NOM_COL, i)->text();
            try {
                DM->suppItem(nom);
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

void DossierDisplayWidget::changed(int, int) {}

void DossierDisplayWidget::change(int, int) {}

void DossierDisplayWidget::displayItem(const QString& item) {
    QString nom, formation, semestresSuivis;

    Dossier n = DM->getItem(item);

    nom = n.getName();
    QStringList f;
    std::vector<Formation> formations = n.getFormations();
    for(auto it=formations.begin(); it!=formations.end(); it++) {
        f<<it->getName();
    }

    QStringList sems;
    std::vector<Semestre> semestres = n.getSemestres();
    for (auto it=semestres.begin(); it!=semestres.end(); it++) {
        sems << it->getName();
    }

    semestresSuivis = sems.join(" ");

    formation = f.join("/");

    if (!ui->searchValue->text().isEmpty()) {
        QString crit = ui->searchValue->text();
        unsigned int col = ui->searchOptions->currentIndex();
        switch (col) {
            case NOM_COL:
                if (!nom.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case FORM_COL:
                if (!formation.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case SEM_COL:
                if (!semestresSuivis.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            default:
                break;
        }
    }

    ui->tableWidget->setItem(offset, NOM_COL, getUneditableItem(nom));
    ui->tableWidget->setItem(offset, FORM_COL, getUneditableItem(formation));
    ui->tableWidget->setItem(offset, SEM_COL, getUneditableItem(semestresSuivis));

    offset++;
}

void DossierDisplayWidget::refresh() {
    std::vector<Dossier> dossiers = DM->iterator();

    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(dossiers.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for (auto it=dossiers.begin(); it!=dossiers.end(); it++) {
        displayItem((*it).getName());
    }
}


