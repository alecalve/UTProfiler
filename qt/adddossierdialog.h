#ifndef ADDDOSSIERDIALOG_H
#define ADDDOSSIERDIALOG_H

#include <QDialog>

#include "src/dossier.hpp"

namespace Ui {
class AddDossierDialog;
}

class AddDossierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDossierDialog(QWidget *parent = 0);
    explicit AddDossierDialog(QWidget *parent = 0, Dossier &d=&Dossier());
    ~AddDossierDialog();

public slots:
    void formationAdded();
    void createDossier();

private:
    Ui::AddDossierDialog *ui;
    QStringList formations;

    bool editionMode;
    Dossier& dossier;
};

#endif // ADDDOSSIERDIALOG_H
