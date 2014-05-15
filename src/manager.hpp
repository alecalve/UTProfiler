#ifndef MANAGER_H
#define MANAGER_H 1

#include <vector>
#include <string>

#include "abstractio.hpp"
#include "singleton.hpp"

#include <iostream>

 //! Classe template représentant les managers de ressources (UVs, filières, ...)
template<class T> class Manager {

  friend class Singleton<Manager>;

  public:
    //! Ajoute la gestion d'un objet au manager
    void addItem(const T& t) {
        elements.push_back(t);
    }

     //! Retourne un objet identifié par une string
    const T& getItem(const std::string &s) const;
    inline void load() {
        elements = ioPolicy->load();
    }

    //! Sauvegarde les objets en utilisant la stratégie définie auparavant
    void save();

    //! Retourne un itérateur (vector) contenant les objets du manager
    std::vector<T> iterator() { return elements; }

    //! Détermine la stratégie de sauvegarde et de chargement des objets
    void setPolicy(AbstractIo *p) {
        ioPolicy = p;
    }

    ~Manager() { delete ioPolicy; }

  private:
    Manager() {}
    Manager(const Manager &) {}
    Manager operator=(const Manager&) {}

    //! Stocke les éléments gérés par le manager
    std::vector<T> elements;

    //! Défini le comportement de sauvegarde des objets
    AbstractIo *ioPolicy;

};

#endif // UVMANAGER_H

