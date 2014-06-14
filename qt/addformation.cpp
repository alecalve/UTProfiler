#include "addformation.h"
#include "ui_addformation.h"

#include <QMessageBox>

#include "src/formation.hpp"

#define UVM UvManager::getInstance()
#define CUM CategorieUVManager::getInstance()
#define FM FormationManager::getInstance()

//! Ouverture du Pop Up Création de formation
AddFormation::AddFormation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFormation)
{
    ui->setupUi(this);

    ui->boxCat->addItems(CUM->getItemNameList());
    ui->boxParent->addItem("Pas de parent");
    ui->boxParent->addItems(FM->getItemNameList());

    QStringList header;
    header << "Catégorie" << "Crédits minimum";
    ui->tableCredits->setColumnCount(2);
    ui->tableCredits->setHorizontalHeaderLabels(header);
    ui->tableCredits->setRowCount(0);
    ui->tableCredits->verticalHeader()->setVisible(false);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList headerUV;
    headerUV << "Nom";
    ui->tableUV->setColumnCount(1);
    ui->tableUV->setHorizontalHeaderLabels(headerUV);
    ui->tableUV->setRowCount(0);
    ui->tableUV->verticalHeader()->setVisible(false);
    ui->tableUV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//! Création d'une formation (ex : GI, GP)
//! Récupération du code et du nom dans 2 champs texte, puis appel du constructeur de la classe formation.
void AddFormation::createFormation() {
    QString abbr, nom;
    abbr = ui->abbrEdit->text();
    nom = ui->nomEdit->text();
    Formation form(abbr,nom);

    QString parent = ui->boxParent->currentText();

    if (ui->boxParent->currentIndex() != 0) {
        std::cout<<ui->boxParent->currentIndex()<<std::endl;
        form.setParent(parent);
    }

    FM->addItem(form);
    close();
}

//! Ajout d'UV à la formation
//! Recupération du code de l'uv dans un champ texte puis on vérifie que l'uv existe et n'a pas déja été ajoutée.
void AddFormation::uvAdded(){

    QString code = ui->uvEdit->text();

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
    for(int i=0; i<ui->tableUV->rowCount(); i++) {
        if(ui->tableUV->item(i, 0)->text() == code) {
            ui->uvEdit->clear();
            return;
        }
    }

    ui->tableUV->setRowCount(ui->tableUV->rowCount() + 1);
    ui->tableUV->setItem(ui->tableUV->rowCount()-1, 0, new QTableWidgetItem(code));
}

void AddFormation::creditsAdded(){

    /*QString code = ui->
    try {
        UVM->getItem(code);
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }*/
}


AddFormation::~AddFormation()
{
    delete ui;
}
