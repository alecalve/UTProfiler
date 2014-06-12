#ifndef ADDDOSSIERDIALOG_H
#define ADDDOSSIERDIALOG_H

#include <QDialog>

namespace Ui {
class AddDossierDialog;
}

class AddDossierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDossierDialog(QWidget *parent = 0);
    ~AddDossierDialog();

public slots:
    void formationAdded();
    void createDossier();

private:
    Ui::AddDossierDialog *ui;
    QStringList formations;
};

#endif // ADDDOSSIERDIALOG_H
