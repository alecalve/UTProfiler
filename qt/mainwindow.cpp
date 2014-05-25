#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

#include "src/xmlio.hpp"
#include "src/exceptions.hpp"

#define UVM UvManager::getInstance()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
    UvManager::freeInstance();
}


void MainWindow::afficheUvs() {

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

    ui->uvdisplay->refresh();
}

void MainWindow::saveUvs() {
    UVM->save();
}
