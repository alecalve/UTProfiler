#include "uvdisplaywidget.h"
#include "ui_displaywidget.h"

#include <QTableWidget>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>

#include "changesemestredialog.h"
#include "changecreditsdialog.h"
#include "src/uvmanager.hpp"
#include "src/exceptions.hpp"

#define UVM UvManager::getInstance()
#define NBCOLS 4
#define CODE_COL 0
#define DESCR_COL 1
#define CREDS_COL 2
#define OUV_COL 3

UvDisplayWidget::UvDisplayWidget(QWidget *parent) :
    DisplayWidget(parent)
{
    QStringList cols;
    cols<<"Code"<<"Description"<<"Crédits"<<"Ouverture";
    ui->searchOptions->addItems(cols);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(NBCOLS);
    ui->tableWidget->setHorizontalHeaderLabels(cols);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

UvDisplayWidget::~UvDisplayWidget() {  }

void UvDisplayWidget::add() {}

void UvDisplayWidget::del() {
    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();

    if (ranges.length() == 0) {
        QMessageBox error(this);
        error.setText("Aucune ligne sélectionnée");
        error.exec();
        return;
    }

    for(auto it=ranges.begin(); it!=ranges.end(); it++) {
        for(int i=it->bottomRow(); i>=it->topRow(); --i) {
            QString code = ui->tableWidget->itemAt(CODE_COL, i)->text();
            std::cout<<i<<" "<<code.toStdString()<<std::endl;
            try {
                UVM->suppItem(code);
            } catch (const Exception &e) {
                QMessageBox error(this);
                error.setText(e.getinfo());
                error.exec();
                return;
            }
        }
    }

    refresh();
}

void UvDisplayWidget::changed(int row, int column) {
    QString code = ui->tableWidget->item(row, CODE_COL)->text();
    QString value = ui->tableWidget->item(row, column)->text();
    Uv& concerned = UVM->getItem(code);

    switch (column) {
        case DESCR_COL:
            concerned.setDescription(value);
            break;
        default:
            break;
    }
}

void UvDisplayWidget::filter(QString) {
    refresh();
}

void UvDisplayWidget::change(int row, int column) {
    QString code = ui->tableWidget->item(row, CODE_COL)->text();

    switch (column) {
        case OUV_COL: {
            ChangeSemestreDialog* dialog = new ChangeSemestreDialog(this, code);
            if (dialog->exec() == 1) { refresh(); }
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

void UvDisplayWidget::displayItem(const QString& item) {
    QString code, descr, ouv, rec;
    QStringList ouvertures, recs;
    Uv u = UVM->getItem(item);

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

    if (!ui->searchValue->text().isEmpty()) {
        QString crit = ui->searchValue->text();
        unsigned int col = ui->searchOptions->currentIndex();
        switch (col) {
            case CODE_COL:
                if (!code.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case CREDS_COL:
                if (!rec.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case DESCR_COL:
                if (!descr.contains(crit, Qt::CaseInsensitive)) { return; }
                break;

            case OUV_COL:
                if (!ouv.contains(crit , Qt::CaseInsensitive)) { return; }
                break;

            default:
                break;
        }
    }

    ui->tableWidget->setItem(offset, CODE_COL, new QTableWidgetItem(code));
    ui->tableWidget->setItem(offset, DESCR_COL, new QTableWidgetItem(descr));
    ui->tableWidget->setItem(offset, OUV_COL, new QTableWidgetItem(ouv));
    ui->tableWidget->setItem(offset, CREDS_COL, new QTableWidgetItem(rec));

    offset++;
}

void UvDisplayWidget::refresh() {
    std::vector<Uv> uvs = UVM->iterator();

    ui->tableWidget->clearContents();
    offset = 0;
    ui->tableWidget->setRowCount(uvs.size());
    ui->tableWidget->setColumnCount(NBCOLS);

    for (auto it=uvs.begin(); it!=uvs.end(); it++) {
        displayItem((*it).getCode());
    }
}
