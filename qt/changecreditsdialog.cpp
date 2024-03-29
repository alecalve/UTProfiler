#include "changecreditsdialog.h"
#include "ui_changecreditsdialog.h"

#include <QMessageBox>

#include "src/structures.hpp"
#include "src/uvmanager.hpp"
#include "src/exceptions.hpp"

#define CUM CategorieUVManager::getInstance()
#define UVM UvManager::getInstance()

//! Ouverture du Pop up de changement de crédits pour l'UV selectionnée
ChangeCreditsDialog::ChangeCreditsDialog(QWidget *parent, QString u) :
    QDialog(parent),
    ui(new Ui::ChangeCreditsDialog)
{
    ui->setupUi(this);
    uv = u;

    try {
        UVM->getItem(uv);

    } catch(const Exception &e) {
        QMessageBox error(this);
        error.setText("UV inconnue");
        error.exec();
    }

    ui->credits->setMinimum(0);
    ui->categories->addItems(CUM->getItemNameList());

    QStringList header;
    header << "Crédits" << "Catégorie";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this, SIGNAL(accepted()), this, SLOT(closing()));
}

//! Ajout de crédits dans une catégorie pour une UV
void ChangeCreditsDialog::ajouter() {
    QString credits = QString::number(ui->credits->value());
    QString categorie =  ui->categories->currentText();
    ui->credits->clear();

    //Si des crédits ont déjà été rajoutés pour cette catégorie,
    //On ignore l’ajout
    for(int i=0; i<ui->tableWidget->rowCount(); i++) {
        if(ui->tableWidget->item(i, 1)->text() == categorie) {
            return;
        }
    }

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(credits));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(categorie));
}

//! fermeture du pop up et sauvegarde des nouveaux crédits
void ChangeCreditsDialog::closing() {
    Uv& concerned = UVM->getItem(uv);
    concerned.resetCredits();
    for(int i=0; i<ui->tableWidget->rowCount(); i++) {
        unsigned int credits;
        credits = ui->tableWidget->item(i, 0)->text().toUInt();
        concerned.setCredits(ui->tableWidget->item(i, 1)->text(), credits);
    }
}

ChangeCreditsDialog::~ChangeCreditsDialog() {
    delete ui;
}
