#include "notedisplaywidget.h"
#include "ui_displaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "src/structures.hpp"
#include "src/exceptions.hpp"

#include <iostream>


#define NUM NoteUVManager::getInstance()
#define NBCOLS 2
#define NOM_COL 0
#define REUSSITE_COL 1

NoteDisplayWidget::NoteDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Nom"<<"Réussite";
    ui->searchOptions->addItems(cols);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->modifyButton->setVisible(false);
}

NoteDisplayWidget::~NoteDisplayWidget() {  }

void NoteDisplayWidget::add() {}

void NoteDisplayWidget::del() {
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
                NUM->suppItem(nom);
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

void NoteDisplayWidget::changed(int, int) {}

void NoteDisplayWidget::change(int row, int column) {
    NoteUV& concerned = NUM->getItem(ui->tableWidget->item(row, NOM_COL)->text());

    switch (column) {
        case REUSSITE_COL:
            QMessageBox::Button reply;
            reply = QMessageBox::question(this, "Changement réussite", "Cette note permet-elle de valider l’UV ?",
                                          QMessageBox::No|QMessageBox::Yes);
            concerned.setReussite(reply == QMessageBox::Yes);
            break;
        default:
            break;
    }

    refresh();
}

void NoteDisplayWidget::displayItem(const QString& item) {
    QString nom, reussite;

    NoteUV n = NUM->getItem(item);

    nom = n.getName();
    reussite = n.getReussite() ? "Oui" : "Non";

    if (!ui->searchValue->text().isEmpty()) {
        QString crit = ui->searchValue->text();
        unsigned int col = ui->searchOptions->currentIndex();
        switch (col) {
            case NOM_COL:
                if (!nom.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            default:
                break;
        }
    }

    QTableWidgetItem *nameItem = new QTableWidgetItem(nom);
    nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
    ui->tableWidget->setItem(offset, NOM_COL, nameItem);
    ui->tableWidget->setItem(offset, REUSSITE_COL, new QTableWidgetItem(reussite));

    offset++;
}

void NoteDisplayWidget::refresh() {
    std::vector<NoteUV> notes = NUM->iterator();

    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(notes.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for (auto it=notes.begin(); it!=notes.end(); it++) {
        displayItem((*it).getName());
    }
}

