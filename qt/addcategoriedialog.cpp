#include "addcategoriedialog.h"
#include "ui_addcategoriedialog.h"

#include "src/structures.hpp"

#define CUM CategorieUVManager::getInstance()

AddCategorieDialog::AddCategorieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategorieDialog)
{
    ui->setupUi(this);
}

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
