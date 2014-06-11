#include "changecreditsdialog.h"
#include "ui_changecreditsdialog.h"

#include <QMessageBox>

#include "src/structures.hpp"
#include "src/uvmanager.hpp"
#include "src/exceptions.hpp"

#define CUM CategorieUVManager::getInstance()
#define UVM UvManager::getInstance()

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

    QStringList categories;
    std::vector<CategorieUV> iterator = CUM->iterator();
    for(auto it=iterator.begin(); it!=iterator.end(); it++) {
        categories << it->getName();
    }


    ui->credits->setMinimum(0);
    ui->categories->addItems(categories);

    QStringList header;
    header << "Crédits" << "Catégorie";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this, SIGNAL(accepted()), this, SLOT(closing()));
}

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
