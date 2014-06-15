#include "exigencesdialog.h"
#include "ui_exigencesdialog.h"

#include <QMessageBox>

#include "src/uvmanager.hpp"
#include "src/solvingcontext.hpp"
#include "src/strategy.hpp"

#define UVM UvManager::getInstance()
#define NB_COLS 1

ExigencesDialog::ExigencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExigencesDialog)
{
    ui->setupUi(this);

    QStringList header;
    header << "Code";

    ui->tableWish->setColumnCount(NB_COLS);
    ui->tableWish->setHorizontalHeaderLabels(header);
    ui->tableWish->setRowCount(0);
    ui->tableWish->verticalHeader()->setVisible(false);
    ui->tableWish->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableReject->setColumnCount(NB_COLS);
    ui->tableReject->setHorizontalHeaderLabels(header);
    ui->tableReject->setRowCount(0);
    ui->tableReject->verticalHeader()->setVisible(false);
    ui->tableReject->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ExigencesDialog::~ExigencesDialog()
{
    delete ui;
}

void ExigencesDialog::wishAdded() {
    QString code = ui->wish->text();

    ui->wish->clear();

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
    for(int i=0; i<ui->tableWish->rowCount(); i++) {
        if(ui->tableWish->item(i, 0)->text() == code) {
            return;
        }
    }

    ui->tableWish->setRowCount(ui->tableWish->rowCount() + 1);
    ui->tableWish->setItem(ui->tableWish->rowCount()-1, 0, new QTableWidgetItem(code));

}

void ExigencesDialog::rejectAdded() {
    QString code = ui->reject->text();

    ui->reject->clear();

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
    for(int i=0; i<ui->tableReject->rowCount(); i++) {
        if(ui->tableReject->item(i, 0)->text() == code) {
            return;
        }
    }

    ui->tableReject->setRowCount(ui->tableReject->rowCount() + 1);
    ui->tableReject->setItem(ui->tableReject->rowCount()-1, 0, new QTableWidgetItem(code));

}

void ExigencesDialog::resolve() {
    SolvingContext context;

    for(int i=0; i<ui->tableWish->rowCount(); i++) {
        context.addWish(ui->tableWish->item(i, 0)->text());
    }

    for(int i=0; i<ui->tableReject->rowCount(); i++) {
        context.addRejection(ui->tableReject->item(i, 0)->text());
    }

    Completion completion;
    completion.setStrategy(new ConcreteStrategy());
    completion.solve(*dossier, context);

    accept();
}
