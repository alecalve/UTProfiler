#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/xmlio.hpp"

#include <iostream>

#define UVM UvManager::getInstance()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    UVM->setPolicy(new XmlIo("/home/antoine/uvs.xml"));
    UVM->load();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::afficheUvs() {
    UVM->setPolicy(new XmlIo("/home/antoine/uvs.xml"));
    UVM->load();
    std::vector<Uv> uvs = UVM->iterator();
    for(auto it=uvs.begin(); it!=uvs.end(); it++) {
        QString code = QString::fromStdString(it->getCode());
        ui->plainTextEdit->appendPlainText(code);
    }
}
