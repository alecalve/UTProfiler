#ifndef MANAGER_H
#define MANAGER_H 1

#include <vector>
#include <string>
#include <iostream>

#include <QStringList>

#include "singleton.hpp"
#include "exceptions.hpp"


//! Item de base destiné à être stocké par un manager
class BaseItem {

  public:

    //! Constructeur par défaut
    BaseItem() : name("BaseItem") {}

    //! Constructeur de base, prends en arguments
    BaseItem(const QString& n): name(n) {}

    //! Retourne le nom de l’objet
    const QString& getName() const { return name; }

    //! Met à jour le nom de l’objet
    void setName(const QString& n) { name = n; }

    //! Opérateur d’égalité, se base sur le nom
    bool operator==(const BaseItem& b) const { return (name == b.getName());}

    //! Opérateur de comparaison, se base sur le nom
    bool operator<(const BaseItem& b) const { return (name<b.getName()); }

  protected:

    //! Nom de l’objet
    QString name;

};

//! Classe template représentant les managers de ressources (UVs, filières, ...)
//! Les objets représentés doivent hériter de BaseItem
template<class T> class Manager {

  friend class Singleton<Manager>;

  public:
    //! Ajoute la gestion d'un objet au manager
    void addItem(T t) {
        elements.push_back(t);
    }

    //! Retourne un objet identifié par une string (QString)
    T& getItem(const QString &s) const {
        int index = -1;
        for (auto it=elements.begin(); it!=elements.end(); it++) {
            index++;
            if (it->getName() == s) {
                T& item = const_cast<T&>(elements.at(index));
                return item;
            }
        }

        throw Exception("Objet non trouvé.");
    }


    //! Retourne un itérateur (vector) contenant les objets du manager
    std::vector<T> iterator() { return elements; }


    //! Retourne un liste des noms des objets du manager
    QStringList getItemNameList() {
        QStringList list;
        for(auto it=elements.begin(); it!=elements.end(); it++) {
            list<<it->getName();
        }
        return list;
    }

    //! Suppression d'un élément.
    void suppItem(const QString& s) {
        T item = getItem(s);
        bool found = false;

        for(auto it=elements.begin(); !found && it!=elements.end(); it++) {
            if (*it == item) {
                //On met it = devant pour ne pas invalider l’iterateur
                //Sinon si on supprime des élements pendant une itération
                //sans mettre à jour l’itérateur il se passe n’importe quoi
                it = elements.erase(it);
                found = true;
            }
        }
    }

  private:
    Manager() {}
    Manager(const Manager &) {}
    Manager operator=(const Manager&) {}

    //! Stocke les éléments gérés par le manager
    std::vector<T> elements;

};

#endif // UVMANAGER_H

