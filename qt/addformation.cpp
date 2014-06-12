#include "addformation.h"
#include "ui_addformation.h"
#include <QMessageBox>


#include "src/formation.hpp"

#define UVM UvManager::getInstance()
#define CUM CategorieUVManager::getInstance()

addformation::addformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addformation)
{
    ui->setupUi(this);
}


void addformation::createFormation() {
    close();
    QString abbr, nom;
    abbr = ui->abbrEdit->text();
    nom = ui->nomEdit->text();
    Formation form(abbr,nom);

    // à mettre dans quel uvmanager ?
}

void addformation::uvAdded(){

        QString code = ui->UvBox->currentText();
        try {
            UVM->getItem(code);
        } catch(const Exception& e) {
            QMessageBox error(this);
            error.setText(e.getinfo());
            error.exec();
            return;
        }

    if (ui->checkUvoblig->isChecked()) {
        form.compulsory.pushback(UVM->getItem(code));
    }
    else form.recommended.pushback(UVM->getItem(code));
}


void addformation::formationparente() {
    QString fparent = ui->comboBoxParent->currentText();
    form.parent = fparent;
}


void addformation::minUvRecommended() {
    unsigned int mini = ui->miniUv->value();
    form.parent = mini;
}

void addformation::nbCreditCat() {
    QString cat = ui->BoxCat->currentText();
    unsigned int nbr = ui->spinCatmin->value();
    form.requirements[cat]=nbr;
    form.minCredits += nbr;

}

addformation::~addformation()
{
    delete ui;
}
