#ifndef CATEGORIEDISPLAYWIDGET_H
#define CATEGORIEDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class CategorieDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    CategorieDisplayWidget(QWidget *parent = 0);
    ~CategorieDisplayWidget();
    void displayItem(const QString&);

    //! 6 fonctions pour la fenetre des catégories : refresh pour rafraichir la fenetre, del pour supprimer une catégorie,
    //! add pour ajouter une catégorie, modify pour modifier une catégorie, changed pour mettre a jour la valeur recuperer dans les champs text
    //! change pour lancer les widgets pour mettre a jour les informations
  public slots:
    void refresh();
    void del();
    void add();
    void modify();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // CATEGORIEDISPLAYWIDGET_H
