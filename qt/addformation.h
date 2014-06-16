#ifndef ADDFORMATION_H
#define ADDFORMATION_H 1

#include <QDialog>

#include "src/formation.hpp"

namespace Ui {
class AddFormation;
}

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
    //! Fonction pour créer une formation, ajouter une uv à la formation et ajouter le nombre de crédit à obtenir pour la formation
    void createFormation();
    void uvAdded();
    void creditsAdded();

    //! attribut de la fenetre d'ajout de formation
private:
    Ui::AddFormation *ui;

    //! Formation à créer ou modifier
    Formation formation;

    //! Indique si le dialog doit éditer ou crée la formation
    bool editionMode;
};

#endif // ADDFORMATION_H
