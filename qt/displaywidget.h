#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();
    virtual void displayItem(const QString&)=0;

    //! 6 fonctions pour la fenetre des catégories : refresh pour rafraichir la fenetre, del pour supprimer une catégorie,
    //! add pour ajouter une catégorie, modify pour modifier une catégorie, changed pour mettre a jour la valeur recuperer dans les champs text
    //! change pour lancer les widgets pour mettre a jour les informations
public slots:
    virtual void refresh()=0;
    virtual void add()=0;
    virtual void del()=0;
    virtual void modify()=0;
    virtual void change(int row, int column)=0;
    virtual void changed(int row, int column)=0;
    inline void filter(QString) { refresh(); }


protected:
    Ui::DisplayWidget *ui;

    inline QTableWidgetItem *getUneditableItem(const QString& data) {
        QTableWidgetItem *item= new QTableWidgetItem(data);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        return item;
    }

    unsigned int offset;
};

#endif // DISPLAYWIDGET_H
