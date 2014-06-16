#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class DisplayWidget;
}

//! Classe abstraite pour afficher les objets gérés par des Managers
class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

    //! Affiche un objet
    virtual void displayItem(const QString&)=0;

public slots:
    //! Met à jour l’UI
    virtual void refresh()=0;

    //! Déclenche l’ajout d’un objet
    virtual void add()=0;

    //! Supprime les objets sélectionnés
    virtual void del()=0;

    //! Modifie l’objet courant
    virtual void modify()=0;

    //! Appelé en cas de click sur une case
    virtual void change(int row, int column)=0;

    //! Appelé en cas de changement de valeur d’une case
    virtual void changed(int row, int column)=0;

    //! Filtre les objets
    inline void filter(QString) { refresh(); }


protected:
    Ui::DisplayWidget *ui;

    inline QTableWidgetItem *getUneditableItem(const QString& data) {
        QTableWidgetItem *item= new QTableWidgetItem(data);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        return item;
    }

    //! Ligne courante du tableau
    unsigned int offset;
};

#endif // DISPLAYWIDGET_H
