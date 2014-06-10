#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

#include "src/xmlio.hpp"
#include "src/exceptions.hpp"
#include "addsemestredialog.h"

#define UVM UvManager::getInstance()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QMainWindow::showMaximized();
}

MainWindow::~MainWindow() {
    delete ui;
    UvManager::freeInstance();
}


void MainWindow::loadFile() {

    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    if (filename.isNull()) { return; }

    UVM->setPolicy(new XmlIo(filename));
    try {
        UVM->load();
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
        return;
    }

    ui->uvDisplay->refresh();
    ui->noteDisplay->refresh();
    ui->categorieDisplay->refresh();
}

void MainWindow::saveFile() {
    if (UVM->hasPolicyDefined()) {
        UVM->save();
    } else {
        QMessageBox error(this);
        error.setText("Aucune donnée chargée");
        error.exec();
        return;
    }
}
