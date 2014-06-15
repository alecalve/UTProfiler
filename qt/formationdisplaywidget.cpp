#include "formationdisplaywidget.h"
#include "ui_displaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "src/formation.hpp"
#include "src/exceptions.hpp"
#include "addformation.h"

#define FM FormationManager::getInstance()
#define NBCOLS 4
#define ABBR_COL 0
#define NOM_COL 1
#define PARENT_COL 2
#define NUV_COL 3

//! Onglet de gestion des formations
FormationDisplayWidget::FormationDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Abbréviation"<<"Nom"<<"Formation parente"<<"Nombre d’UVs dans la formation";
    ui->searchOptions->addItems(cols);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

FormationDisplayWidget::~FormationDisplayWidget() {  }
void FormationDisplayWidget::modify() {}

void FormationDisplayWidget::add() {
    AddFormation *dialog = new AddFormation(this);
    dialog->exec();
    delete dialog;

    refresh();

}

void FormationDisplayWidget::del() {
    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();

    if (ranges.length() == 0) {
        QMessageBox error(this);
        error.setText("Aucune ligne sélectionnée");
        error.exec();
        return;
    }

    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString nom = ui->tableWidget->item(i, ABBR_COL)->text();
            try {
                FM->suppItem(nom);
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

void FormationDisplayWidget::changed(int, int) {}

void FormationDisplayWidget::change(int, int) {}

void FormationDisplayWidget::displayItem(const QString& item) {
    QString nom, abbr, parent, nuv;

    Formation f = FM->getItem(item);

    nom = f.getLongName();
    abbr = f.getName();
    nuv = QString::number(f.getUvs().size());

    if (f.hasParent()) {
        parent = f.getParent().getName();
    } else {
        parent = "Pas de parent";
    }

    if (!ui->searchValue->text().isEmpty()) {
        QString crit = ui->searchValue->text();
        unsigned int col = ui->searchOptions->currentIndex();
        switch (col) {
            case NOM_COL:
                if (!nom.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case ABBR_COL:
                if (!abbr.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case PARENT_COL:
                if (!parent.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case NUV_COL:
                if (!nuv.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            default:
                break;
        }
    }

    ui->tableWidget->setItem(offset, NOM_COL, getUneditableItem(nom));
    ui->tableWidget->setItem(offset, ABBR_COL, getUneditableItem(abbr));
    ui->tableWidget->setItem(offset, PARENT_COL, getUneditableItem(parent));
    ui->tableWidget->setItem(offset, NUV_COL, getUneditableItem(nuv));

    offset++;
}

void FormationDisplayWidget::refresh() {
    std::vector<Formation> formations = FM->iterator();

    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(formations.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for (auto it=formations.begin(); it!=formations.end(); it++) {
        displayItem((*it).getName());
    }
}



