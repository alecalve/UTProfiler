#ifndef EXIGENCESDIALOG_H
#define EXIGENCESDIALOG_H

#include <QDialog>

#include "src/dossier.hpp"

namespace Ui {
class ExigencesDialog;
}

class ExigencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExigencesDialog(QWidget *parent = 0);
    ~ExigencesDialog();
    inline void setDossier(Dossier *d) { dossier = d; }

public slots:
    //! Resolve pour lancer la complétion du dossier, wishAdded pour ajouter un souhai d'uv,
    //!rejectAdded pour ajouter un refus de faire une uv
    void resolve();
    void wishAdded();
    void rejectAdded();

private:
    //! Attribut privé : le dossier à compléter, et la fenetre de dialogue d'ajout de souhaits.
    Ui::ExigencesDialog *ui;
    Dossier *dossier;
};

#endif // EXIGENCESDIALOG_H
