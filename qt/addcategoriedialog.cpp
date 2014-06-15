#include "addcategoriedialog.h"
#include "ui_addcategoriedialog.h"

#include "src/structures.hpp"

#define CUM CategorieUVManager::getInstance()
//! Ouverture du Pop up de création de catégorie
AddCategorieDialog::AddCategorieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategorieDialog)
{
    ui->setupUi(this);
}

//! Création d'une nouvelle catégorie (équivalente aux CS/TM/TSH)
//! Récupération du code et du nom dans un champ de texte
void AddCategorieDialog::createCategorie() {
    close();
    QString abbr, nom;
    abbr = ui->abbrEdit->text();
    nom = ui->nomEdit->text();
    CategorieUV cat(abbr, nom);
    CUM->addItem(cat);
}

AddCategorieDialog::~AddCategorieDialog()
{
    delete ui;
}
