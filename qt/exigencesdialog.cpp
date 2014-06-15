#include "exigencesdialog.h"
#include "ui_exigencesdialog.h"

ExigencesDialog::ExigencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExigencesDialog)
{
    ui->setupUi(this);
}

ExigencesDialog::~ExigencesDialog()
{
    delete ui;
}

void ExigencesDialog::resolve() {

}
