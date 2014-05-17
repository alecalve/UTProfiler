#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/xmlio.hpp"

#include <QTableWidget>
#include <QStandardItem>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

#include "src/exceptions.hpp"

#define UVM UvManager::getInstance()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QStringList cols;
    cols<<"Code"<<"Description"<<"Ouverture";

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
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


    std::vector<Uv> uvs = UVM->iterator();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(uvs.size());
    ui->tableWidget->setColumnCount(3);

    unsigned int i=0;
    for(auto it=uvs.begin(); it!=uvs.end(); it++) {
        QString code, descr, ouv;
        QStringList ouvertures;
        code = it->getCode();
        descr = it->getDescription();

        if (it->getOuverturePrintemps()) { ouvertures<<"Automne"; }
        if (it->getOuvertureAutomne()) { ouvertures<<"Printemps"; }

        ouv = ouvertures.join("/");

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(code));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(descr));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(ouv));
        i++;
    }
}

void MainWindow::saveUvs() {

    try {
        UVM->save();
    } catch(const Exception& e) {
        QMessageBox error(this);
        error.setText(e.getinfo());
        error.exec();
    }
}
