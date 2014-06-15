#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "src/xmlio.hpp"
#include "src/exceptions.hpp"
#include "addsemestredialog.h"
#include "src/dossier.hpp"
#include "choosedossierdialog.h"

#define UVM UvManager::getInstance()


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ioPolicy = 0;
    QMainWindow::showMaximized();
}

MainWindow::~MainWindow() {
    delete ui;
    UvManager::freeInstance();
    FormationManager::freeInstance();
    CategorieUVManager::freeInstance();
    DossierManager::freeInstance();
    NoteUVManager::freeInstance();
}

//! Fonction de chargement du ficher contenant les uvs
void MainWindow::loadFile() {

    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    if (filename.isNull()) { return; }

    ioPolicy = new XmlIo();
    ioPolicy->setIdentifier(filename);

    try {
        ioPolicy->load();
    } catch(const Exception& e) {
        delete ioPolicy;
        ioPolicy = 0;
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }


    ui->uvDisplay->refresh();
    ui->noteDisplay->refresh();
    ui->categorieDisplay->refresh();
    ui->formationDisplay->refresh();
}

//! Fonction de sauvegarde du fichier
void MainWindow::saveFile() {
    if (ioPolicy != 0) {
        ioPolicy->save();
    } else {
        QMessageBox error(this);
        error.setText("Aucune donnée chargée");
        error.exec();
        return;
    }
}

void MainWindow::completeDossier() {
    ChooseDossierDialog *dialog = new ChooseDossierDialog(this);
    dialog->exec();
    delete dialog;
}
