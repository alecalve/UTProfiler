#ifndef ADDSEMESTREDIALOG_H
#define ADDSEMESTREDIALOG_H

#include <QDialog>

#include "src/dossier.hpp"

namespace Ui {
class AddSemestreDialog;
}

class AddSemestreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSemestreDialog(QWidget *parent = 0, Dossier *d=NULL);
    ~AddSemestreDialog();

public slots:
  //! Déclenché lors d’un click sur "Ajouter UV"
  void uvAdded();

  //! Déclenché à l’ajout de crédits d’équivalence
  void creditsAdded();

  //! Déclenché à la fermeture du dialog, crée le semestre et met à jour le dossier
  void completeDossier();

  //! dossier dont on souhaite ajouter un semestre d'étude, et fenettre de dialogue d'ajout de semestre
private:
    Ui::AddSemestreDialog *ui;
    Dossier *dossier;
};

#endif // ADDSEMESTREDIALOG_H
