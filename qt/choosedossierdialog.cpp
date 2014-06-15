#include "choosedossierdialog.h"
#include "ui_choosedossierdialog.h"

#include <QMessageBox>

#include "src/dossier.hpp"
#include "exigencesdialog.h"

#define DM DossierManager::getInstance()

ChooseDossierDialog::ChooseDossierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDossierDialog)
{
    ui->setupUi(this);
    ui->dossierBox->addItems(DM->getItemNameList());
}

void ChooseDossierDialog::callCompleter() {
    if (ui->dossierBox->count() == 0) {
        QMessageBox error(this);
        error.setText("Aucun dossier à compléter");
        error.exec();
        close();
        return;
    }

    ExigencesDialog *dialog = new ExigencesDialog(this);
    Dossier d = DM->getItem(ui->dossierBox->currentText());
    dialog->setDossier(&d);
    dialog->exec();
    delete dialog;
    close();

}

ChooseDossierDialog::~ChooseDossierDialog()
{
    delete ui;
}
