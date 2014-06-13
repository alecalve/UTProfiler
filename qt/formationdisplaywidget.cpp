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
#define NBCOLS 3
#define ABBR_COL 0
#define NOM_COL 1
#define PARENT_COL 2

FormationDisplayWidget::FormationDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Abbréviation"<<"Nom"<<"Formation parente";
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
    QString nom, abbr, parent;

    Formation f = FM->getItem(item);

    nom = f.getLongName();
    abbr = f.getName();
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

            default:
                break;
        }
    }

    QTableWidgetItem *nameItem = new QTableWidgetItem(nom);
    nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *abbrItem = new QTableWidgetItem(abbr);
    abbrItem->setFlags(abbrItem->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *parentItem = new QTableWidgetItem(parent);
    parentItem->setFlags(parentItem->flags() & ~Qt::ItemIsEditable);

    ui->tableWidget->setItem(offset, NOM_COL, nameItem);
    ui->tableWidget->setItem(offset, ABBR_COL, abbrItem);
    ui->tableWidget->setItem(offset, PARENT_COL, parentItem);

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



