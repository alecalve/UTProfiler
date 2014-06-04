#include "uvdisplaywidget.h"
#include "ui_uvdisplaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <iostream>

#include "changesemestredialog.h"
#include "src/uvmanager.hpp"
#include <istream>

#define UVM UvManager::getInstance()
#define NBCOLS 4
#define CODE_COL 0
#define DESCR_COL 1
#define CREDS_COL 2
#define OUV_COL 3

UvDisplayWidget::UvDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UvDisplayWidget)
{
    ui->setupUi(this);

    QStringList cols;
    cols<<"Code"<<"Description"<<"Crédits"<<"Ouverture";

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    offset = 0;
}

UvDisplayWidget::~UvDisplayWidget() {
    delete ui;
}


void UvDisplayWidget::changed(int row, int column) {
    QString code = UVM->iterator().at(row).getCode();
    Uv& concerned = UVM->getItem(code);
    QString value = ui->tableWidget->item(row, column)->text();

    switch (column) {
        case CODE_COL:
            concerned.setCode(value);
            break;
        case DESCR_COL:
            concerned.setDescription(value);
            break;
        default:
            break;
    }
}


void UvDisplayWidget::change(int row, int column) {
    Uv concerned = UVM->iterator().at(row);
    if (column == OUV_COL) {
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

void UvDisplayWidget::addUv(const Uv& u) {
    QString code, descr, ouv, rec;
    QStringList ouvertures, recs;
    std::map<QString, unsigned int> recompenses = u.getRecompenses();

    for(const auto &rec : recompenses) {
        QString cat = rec.first;
        QString creds = QString::number(rec.second);
        QStringList l;
        l << creds << cat;
        recs << l.join(" ");
    }

    code = u.getCode();
    descr = u.getDescription();

    if (u.getOuverturePrintemps()) { ouvertures<<"Printemps"; }
    if (u.getOuvertureAutomne()) { ouvertures<<"Automne"; }

    ouv = ouvertures.join("/");
    rec = recs.join(" et ");

    ui->tableWidget->setItem(offset, CODE_COL, new QTableWidgetItem(code));
    ui->tableWidget->setItem(offset, DESCR_COL, new QTableWidgetItem(descr));
    ui->tableWidget->setItem(offset, OUV_COL, new QTableWidgetItem(ouv));
    ui->tableWidget->setItem(offset, CREDS_COL, new QTableWidgetItem(rec));

    offset++;
}

void UvDisplayWidget::addUv(const QString& code) {
    Uv u = UVM->getItem(code);
    ui->tableWidget->setRowCount(offset+1);
    addUv(u);
}

void UvDisplayWidget::refresh() {
    std::vector<Uv> uvs = UVM->iterator();
    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(uvs.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for(auto it=uvs.begin(); it!=uvs.end(); it++) {
        addUv(*it);
    }
}
