#include "addsemestredialog.h"
#include "ui_addsemestredialog.h"

#include <QMessageBox>
#include "src/uvmanager.hpp"
#include "src/exceptions.hpp"
#include "src/equivalence.hpp"

#define UVM UvManager::getInstance()
#define NUM NoteUVManager::getInstance()
#define CUM CategorieUVManager::getInstance()

//! Creation du pop up d'ajout de semestre
AddSemestreDialog::AddSemestreDialog(QWidget *parent, Dossier *d) :
    QDialog(parent),
    ui(new Ui::AddSemestreDialog) {
    ui->setupUi(this);
    dossier = d;
    ui->noteBox->addItems(NUM->getItemNameList());
    ui->categorieBox->addItems(CUM->getItemNameList());

    QStringList header;
    header << "Code" << "Note";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEnabled(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList header2;
    header2 << "Catégorie" << "Crédits";
    ui->tableCredits->setHorizontalHeaderLabels(header2);
    ui->tableCredits->setRowCount(0);
    ui->tableCredits->setColumnCount(2);
    ui->tableCredits->verticalHeader()->setVisible(false);
    ui->tableCredits->setEnabled(false);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->formationBox->addItems(d->getFormationsName());
}

void AddSemestreDialog::completeDossier() {

    if (ui->semestreEdit->text().isEmpty()) {
        QMessageBox error(this);
        error.setText("Vous devez nommer le semestre !");
        error.exec();
        return;
    }

    SemestreT s(ui->semestreBox->currentText(), (unsigned int) ui->anneeBox->value());
    dossier->setExtraScolaire(ui->extrascolaire->isChecked());

    if (ui->equivalenceCheckBox->isChecked()) {
        Equivalence equivalence(ui->semestreEdit->text(), ui->justificationEdit->text());
        equivalence.setSemestre(s);

        for(int i=0; i<ui->tableCredits->rowCount(); i++) {
            QTableWidgetItem *cat= ui->tableCredits->item(i, 0);
            QTableWidgetItem *creds= ui->tableCredits->item(i, 1);
            equivalence.setCredits(cat->text(), creds->text().toUInt());
        }

        dossier->addEquivalence(equivalence);


    } else {
        Semestre semestre(ui->semestreEdit->text());
        semestre.setSemestre(s);
        semestre.setFormation(FM->getItem(ui->formationBox->currentText()));
        for(int i=0; i<ui->tableWidget->rowCount(); i++) {
            QTableWidgetItem *uv = ui->tableWidget->item(i, 0);
            QTableWidgetItem *note= ui->tableWidget->item(i, 1);
            semestre.setResultat(uv->text(), note->text());
        }

        dossier->addSemestre(semestre);
    }

    close();

}

//! Ajout d'une uv au semestre et de la note obtenue,
//! On vérifie que l'uv n'a pas déja été ajoutée et si elle existe bien
void AddSemestreDialog::uvAdded() {
    QString code = ui->codeEdit->text();
    QString note = ui->noteBox->currentText();

    ui->codeEdit->clear();

    try {
        UVM->getItem(code);
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }

    //Si cette UV a été rajoutée auparavant
    //On ignore l’ajout
    for(int i=0; i<ui->tableWidget->rowCount(); i++) {
        if(ui->tableWidget->item(i, 0)->text() == code) {
            return;
        }
    }

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(code));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(note));

}

void AddSemestreDialog::creditsAdded() {
    unsigned int c = ui->creditsBox->value();
    QString creds = QString::number(c);
    QString cat = ui->categorieBox->currentText();

    ui->creditsBox->clear();

    try {
        CUM->getItem(cat);
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }

    //Si cette catégorie a été rajoutée auparavant on met à jour
    for(int i=0; i<ui->tableCredits->rowCount(); i++) {
        if(ui->tableCredits->item(i, 0)->text() == cat) {
            ui->tableCredits->setItem(i, 1, new QTableWidgetItem(creds));
            return;
        }
    }

    ui->tableCredits->setRowCount(ui->tableCredits->rowCount() + 1);
    ui->tableCredits->setItem(ui->tableCredits->rowCount()-1, 0, new QTableWidgetItem(cat));
    ui->tableCredits->setItem(ui->tableCredits->rowCount()-1, 1, new QTableWidgetItem(creds));
}

AddSemestreDialog::~AddSemestreDialog() {
    delete ui;
}
