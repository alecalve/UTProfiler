#include "addnotedialog.h"
#include "ui_addnotedialog.h"

#include "src/structures.hpp"

#define NUM NoteUVManager::getInstance()

AddNoteDialog::AddNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNoteDialog)
{
    ui->setupUi(this);
}

void AddNoteDialog::createNote() {
    QString note = ui->nomEdit->text();
    bool reussite = ui->checkBox->isChecked();

    NoteUV n(note, reussite);
    NUM->addItem(n);

    close();
}

AddNoteDialog::~AddNoteDialog()
{
    delete ui;
}
