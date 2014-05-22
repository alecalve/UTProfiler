#include "uvdisplaywidget.h"
#include "ui_uvdisplaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <iostream>

#include "changesemestredialog.h"
#include "src/uvmanager.hpp"

#define UVM UvManager::getInstance()

UvDisplayWidget::UvDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UvDisplayWidget)
{
    ui->setupUi(this);

    QStringList cols;
    cols<<"Code"<<"Description"<<"Ouverture";

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

UvDisplayWidget::~UvDisplayWidget() {
    delete ui;
}


void UvDisplayWidget::changed(int row, int column) {
    QString code = UVM->iterator().at(row).getCode();
    Uv& concerned = UVM->getItem(code);
    QString value = ui->tableWidget->item(row, column)->text();

    switch (column) {
        case 0:
            concerned.setCode(value);
            break;
        case 1:
            concerned.setDescription(value);
            break;
        default:
            break;
    }
}


void UvDisplayWidget::change(int row, int column) {
    Uv concerned = UVM->iterator().at(row);
    if (column == 2) {
        ChangeSemestreDialog* dialog = new ChangeSemestreDialog(this,
                                                                concerned.getOuverturePrintemps(),
                                                                concerned.getOuvertureAutomne(),
                                                                row);
        dialog->exec();

    }
}

void UvDisplayWidget::choiceSemestre(int row, bool printemps, bool automne) {
    QString code = ui->tableWidget->item(row, 0)->text();
    Uv& concerned = UVM->getItem(code);
    concerned.setOuvertureAutomne(automne);
    concerned.setOuverturePrintemps(printemps);
    refresh();
}

void UvDisplayWidget::refresh() {
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

        if (it->getOuverturePrintemps()) { ouvertures<<"Printemps"; }
        if (it->getOuvertureAutomne()) { ouvertures<<"Automne"; }

        ouv = ouvertures.join("/");

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(code));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(descr));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(ouv));
        i++;
    }
}
