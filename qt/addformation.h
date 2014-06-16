#ifndef ADDFORMATION_H
#define ADDFORMATION_H 1

#include <QDialog>

namespace Ui {
class AddFormation;
}

class AddFormation : public QDialog
{
    Q_OBJECT

public:
    explicit AddFormation(QWidget *parent = 0);
    ~AddFormation();

    //! Fonction pour créer une formation, ajouter une uv à la formation et ajouter le nombre de crédit à obtenir pour la formation
public slots :
    void createFormation();
    void uvAdded();
    void creditsAdded();

    //! attribut de la fenetre d'ajout de formation
private:
    Ui::AddFormation *ui;
};

#endif // ADDFORMATION_H
