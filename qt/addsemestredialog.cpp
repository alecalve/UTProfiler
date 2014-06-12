#include "addsemestredialog.h"
#include "ui_addsemestredialog.h"

#include <QMessageBox>
#include "src/uvmanager.hpp"
#include "src/exceptions.hpp"

#define UVM UvManager::getInstance()
#define NUM NoteUVManager::getInstance()

AddSemestreDialog::AddSemestreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSemestreDialog) {
    ui->setupUi(this);

    ui->noteBox->addItems(NUM->getItemNameList());
    QStringList header;
    header << "Code" << "Note";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

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

AddSemestreDialog::~AddSemestreDialog() {
    delete ui;
}
