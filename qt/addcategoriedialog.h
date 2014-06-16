#ifndef ADDCATEGORIEDIALOG_H
#define ADDCATEGORIEDIALOG_H

#include <QDialog>
//! Classe pour l'ouverture du pop up de modification/ajout de catégorie
namespace Ui {
class AddCategorieDialog;
}

class AddCategorieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategorieDialog(QWidget *parent = 0);
    ~AddCategorieDialog();

public slots:
    //! Slot de création de la catégorie
    void createCategorie();

private:
    Ui::AddCategorieDialog *ui;
};

#endif // ADDCATEGORIEDIALOG_H
