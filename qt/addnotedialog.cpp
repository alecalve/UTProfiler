#include "addnotedialog.h"
#include "ui_addnotedialog.h"

#include "src/structures.hpp"

#define NUM NoteUVManager::getInstance()

//! Ouverture du Pop Up de création de note
AddNoteDialog::AddNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNoteDialog)
{
    ui->setupUi(this);
}

//! Création d'une note par récupération d'un nom et de la validation ou non de l'uv par l'obtention de celle ci.
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
