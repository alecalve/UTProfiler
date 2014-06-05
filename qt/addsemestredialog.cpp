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
    QStringList notes;
    std::vector<NoteUV> iterator = NUM->iterator();
    for(auto it=iterator.begin(); it!=iterator.end(); it++) {
        notes<<it->nom;
    }
    ui->noteBox->addItems(notes);

}

void AddSemestreDialog::uvAdded() {
    QString code = ui->codeEdit->text();
    QString note = ui->noteBox->currentText();

    try {
        UVM->getItem(code);
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }

    ui->widget->addUv(code);
}

AddSemestreDialog::~AddSemestreDialog() {
    delete ui;
}
