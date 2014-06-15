#include "categoriedisplaywidget.h"
#include "ui_displaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "src/structures.hpp"
#include "src/exceptions.hpp"
#include "addcategoriedialog.h"

#define CUM CategorieUVManager::getInstance()
#define NBCOLS 2
#define NOM_COL 1
#define ABBR_COL 0

//! Onglet des catégories
CategorieDisplayWidget::CategorieDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Nom"<<"Abbréviation";
    ui->searchOptions->addItems(cols);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->modifyButton->setVisible(false);


}

CategorieDisplayWidget::~CategorieDisplayWidget() {  }
void CategorieDisplayWidget::modify() {}

//! Ouverture de l'outil de création de catégorie
void CategorieDisplayWidget::add() {
    AddCategorieDialog *dialog = new AddCategorieDialog(this);
    dialog->exec();
    delete dialog;
    refresh();
}

//! Supresion d'une catégorie
void CategorieDisplayWidget::del() {
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
                CUM->suppItem(nom);
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

void CategorieDisplayWidget::changed(int row, int column) {
    CategorieUV& concerned = CUM->getItem(ui->tableWidget->item(row, ABBR_COL)->text());

    switch (column) {
    case ABBR_COL:
        concerned.setName(ui->tableWidget->item(row, column)->text());
        break;
    default:
        break;
    }
}

void CategorieDisplayWidget::change(int, int) {}

void CategorieDisplayWidget::displayItem(const QString& item) {
    QString nom, abbr;

    CategorieUV n = CUM->getItem(item);

    nom = n.getLongName();
    abbr = n.getName();

    if (!ui->searchValue->text().isEmpty()) {
        QString crit = ui->searchValue->text();
        unsigned int col = ui->searchOptions->currentIndex();
        switch (col) {
            case NOM_COL:
                if (!nom.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case ABBR_COL:
                if (!abbr.contains(crit, Qt::CaseInsensitive)) { return; }

            default:
                break;
        }
    }


    QTableWidgetItem *nameItem = new QTableWidgetItem(abbr);
    nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
    ui->tableWidget->setItem(offset, ABBR_COL, nameItem);
    ui->tableWidget->setItem(offset, NOM_COL, new QTableWidgetItem(nom));

    offset++;
}

//! Raffraichir le tableau
void CategorieDisplayWidget::refresh() {
    std::vector<CategorieUV> categories = CUM->iterator();

    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(categories.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for (auto it=categories.begin(); it!=categories.end(); it++) {
        //std::cout<<it->getName().toStdString()<<std::endl;
        displayItem(it->getName());
    }
}


