#ifndef ADDUVDIALOG_H
#define ADDUVDIALOG_H

#include <QDialog>

namespace Ui {
class AddUVDialog;
}

class AddUVDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUVDialog(QWidget *parent = 0);
    ~AddUVDialog();

public slots:
    //! Fermeture de la fenetre d'ajout d'uv
    void endCreationProcess();

private:

    Ui::AddUVDialog *ui;
};

#endif // ADDUVDIALOG_H
