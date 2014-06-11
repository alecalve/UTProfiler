#ifndef MANAGER_H
#define MANAGER_H 1

#include <vector>
#include <string>

#include "abstractio.hpp"
#include "singleton.hpp"
#include "exceptions.hpp"

class BaseItem {

  public:

    BaseItem(const QString& n): name(n) {}
    const QString& getName() const { return name; }
    void setName(const QString& n) { name = n; }

    bool operator==(const BaseItem& b) const { return (name == b.getName());}
    bool operator<(const BaseItem& b) const { return (name<b.getName()); }

  protected:
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

    //! Indique si une stratégie de sauvegarde a été définie
    bool hasPolicyDefined() {
        return (ioPolicy != 0);
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

    //! Charge les UVs présentes dans la sauvegarde définie par la stratégie ioPolicy
    inline void load() {
        ioPolicy->load();
    }

    //! Sauvegarde les objets sauvegardés en utilisant la stratégie définie auparavant
    void save() { ioPolicy->save(); }

    //! Retourne un itérateur (vector) contenant les objets du manager
    std::vector<T> iterator() { return elements; }

    //! Détermine la stratégie de sauvegarde et de chargement des objets
    void setPolicy(AbstractIo *p) {
        ioPolicy = p;
    }

    //! Suppression d'un élément.
    void suppItem(const QString& s) {
        T item = getItem(s);
        bool found = false;

        for(auto it=elements.begin(); !found && it!=elements.end(); it++) {
            if (found) { break; }
            if (*it == item) {
                //On met it = devant pour ne pas invalider l’iterateur
                //Sinon si on supprime des élements pendant une itération
                //sans mettre à jour l’itérateur il se passe n’importe quoi
                it = elements.erase(it);
                found = true;
            }
        }
    }

    ~Manager() { delete ioPolicy; }

  private:
    Manager() {
        ioPolicy = 0;
    }
    Manager(const Manager &) {}
    Manager operator=(const Manager&) {}

    //! Stocke les éléments gérés par le manager
    std::vector<T> elements;

    //! Défini le comportement de sauvegarde des objets
    AbstractIo *ioPolicy;

};

#endif // UVMANAGER_H

