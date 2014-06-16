#ifndef CHANGECREDITSDIALOG_H
#define CHANGECREDITSDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeCreditsDialog;
}

class ChangeCreditsDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChangeCreditsDialog(QWidget *parent = 0, QString u="");
    ~ChangeCreditsDialog();

    //! fonction pour les boutons d'ajout et de fermeture de la fenetre de dialogue
public slots:
    void ajouter();
    void closing();

    //! Attributs privés : UV dont on souhaite changer le nombre de crédit, et la fenetre graphique dans laquelle
    //! on change le nombre de crédits
private:
    Ui::ChangeCreditsDialog *ui;
    QString uv;
};

#endif // CHANGECREDITSDIALOG_H
