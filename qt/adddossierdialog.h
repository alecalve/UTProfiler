#ifndef ADDDOSSIERDIALOG_H
#define ADDDOSSIERDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include "src/dossier.hpp"

//! Classe pour l'ouverture du pop up pour l'ajout ou la modification de Dossier
namespace Ui {
class AddDossierDialog;
}

class AddDossierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDossierDialog(QWidget *parent = 0);
    ~AddDossierDialog();

    //! En cas d’édition, défini le dossier à éditer
    void setDossier(const QString& name);

    //! En cas de création, crée le dossier vierge
    void setDossier();

public slots:

    //! Slot activé en cas d’ajout de formation, met à jour l’UI et ajoute la
    //! formation à la QStringList formations
    void formationAdded();

    //! Slot activé à la fermeture du dialog, crée/update le dossier
    void createDossier();

    //! Slot activé à l’ajout d’un semestre, met à jour l’UI
    void semestreAdded();

    void semestreRemoved();
    void formationRemoved();

private:
    Ui::AddDossierDialog *ui;

    //! Indique si le dialog doit éditer ou créer un dossier
    bool editionMode;

    //! Rafraîchi les tableaux contenant les formations et semestres
    void refresh();

    inline QTableWidgetItem *getUneditableItem(const QString& data) {
        QTableWidgetItem *item= new QTableWidgetItem(data);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        return item;
    }

    //! Dossier en cours de création ou d’édition
    Dossier dossier;
};

#endif // ADDDOSSIERDIALOG_H
