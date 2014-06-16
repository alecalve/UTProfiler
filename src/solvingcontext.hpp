#ifndef SOLVINGCONTEXT_HPP
#define SOLVINGCONTEXT_HPP

#include <vector>

#include "uv.hpp"
#include "uvmanager.hpp"

#define UVM UvManager::getInstance()

//! Contexte de résolution de la complétion d’un dossier
//! Renferme les contraintes imposées par l’étudiant
class SolvingContext {

  public:
    //! Constructeur par défaut
    SolvingContext() {}

    //! Renvoie la liste des UV dont la réalisation est souhaitée par l’étudiant
    inline const std::vector<Uv>& getWishes() const { return wishes; }

    //! Renvoie la liste des UV dont la réalisation est n’est pas souhaitée par l’étudiant
    inline const std::vector<Uv>& getRejections() const { return rejections; }

    //! Ajoute une UV à la liste des UV souhaitées
    inline void addWish(Uv u) { wishes.push_back(u); }

    //! Ajoute une UV à la liste des UV souhaitées
    inline void addWish(const QString& u) {
        Uv uv = UVM->getItem(u);
        addWish(uv);
    }

    //! Ajoute une UV à la liste des UV non souhaitées
    inline void addRejection(Uv u) { rejections.push_back(u); }

    //! Ajoute une UV à la liste des UV non souhaitées
    inline void addRejection(const QString& u) {
        Uv uv = UVM->getItem(u);
        addRejection(uv);
    }

  private:

    //! Liste des UV dont la réalisation est souhaitée par l’étudiant
    std::vector<Uv> wishes;

    //! Liste des UV dont la réalisation est souhaitée par l’étudiant
    std::vector<Uv> rejections;
};

#endif // SOLVINGCONTEXT_HPP
