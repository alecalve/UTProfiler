#include "uvdisplaywidget.h"
#include "ui_uvdisplaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "changesemestredialog.h"
#include "changecreditsdialog.h"
#include "src/uvmanager.hpp"


#define UVM UvManager::getInstance()
#define NBCOLS 5
#define CODE_COL 0
#define DESCR_COL 1
#define CREDS_COL 2
#define OUV_COL 3
#define DEL_COL 4

UvDisplayWidget::UvDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UvDisplayWidget)
{
    ui->setupUi(this);

    QStringList cols;
    cols<<"Code"<<"Description"<<"Crédits"<<"Ouverture"<<"Suppression";

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
    QString code = ui->tableWidget->item(row, CODE_COL)->text();
    QString value = ui->tableWidget->item(row, column)->text();
    Uv& concerned = UVM->getItem(code);

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
    QString code = ui->tableWidget->item(row, CODE_COL)->text();

    switch (column) {
        case OUV_COL: {
            ChangeSemestreDialog* dialog = new ChangeSemestreDialog(this, code);
            dialog->exec();
            refresh();
            break;
        }
        case DEL_COL: {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmer la suppression de l’UV",
                                                "Voulez-vous vraiment supprimer cette UV ?",
                                                QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                UVM->suppItem(code);
                refresh();
            }
            break;
        }

        case CREDS_COL: {
            ChangeCreditsDialog* dialog = new ChangeCreditsDialog(this, code);
            dialog->exec();
            refresh();
            break;
        }
        default:
            break;
    }
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
    ui->tableWidget->setItem(offset, DEL_COL, new QTableWidgetItem("x"));

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
