#include "changesemestredialog.h"
#include "ui_changesemestredialog.h"

#include <iostream>

ChangeSemestreDialog::ChangeSemestreDialog(QWidget *parent, bool p, bool a, int r) :
    QDialog(parent),
    ui(new Ui::ChangeSemestreDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Ouverture de l'UV");
    row = r;
    ui->printemps->setChecked(p);
    ui->automne->setChecked(a);
    connect(this, SIGNAL(accepted()), this, SLOT(closing()));
}

ChangeSemestreDialog::~ChangeSemestreDialog() {
    delete ui;
}


void ChangeSemestreDialog::closing() {
    if (row != -1) {
        ((UvDisplayWidget*) parentWidget())->choiceSemestre(row, ui->printemps->isChecked(), ui->automne->isChecked());
    }
}
