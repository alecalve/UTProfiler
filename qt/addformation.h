#ifndef ADDFORMATION_H
#define ADDFORMATION_H 1

#include <QDialog>

#include "src/formation.hpp"

namespace Ui {
class AddFormation;
}

//! Dialog de création et d’édition de Formation
class AddFormation : public QDialog
{
    Q_OBJECT

public:
    explicit AddFormation(QWidget *parent = 0);
    ~AddFormation();

    //! Indique la formation à modifier en cas de modifications
    void setFormation(const QString&);

    //! Indique que le dossier doit être créer
    void setFormation();

public slots :

    //! Slot de création de formation, appelé à l’acceptation du dialog
    void createFormation();

    //! Slot appelé en cas d’ajout d’UV
    void uvAdded();

    //! Slot appelé en cas d’ajout de crédits
    void creditsAdded();

private:
    Ui::AddFormation *ui;

    //! Formation à créer ou modifier
    Formation formation;

    //! Indique si le dialog doit éditer ou crée la formation
    bool editionMode;
};

#endif // ADDFORMATION_H
