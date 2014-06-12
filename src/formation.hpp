#ifndef FORMATION_HPP
#define FORMATION_HPP 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "singleton.hpp"
#include "manager.hpp"
#include "uvmanager.hpp"

#include <iostream>

class Formation;
typedef Singleton<Manager<Formation>> FormationManager;

#define CUM CategorieUVManager::getInstance()
#define UVM UvManager::getInstance()
#define FM FormationManager::getInstance()

//! Classe des Formations
class Formation : public BaseItem {

  public:

    Formation(const QString& abbr, const QString& n)
        : BaseItem(abbr), longName(n), parent(""), nbLignes(0), nbColonnes(0),
          minCredits(0), minNbUvRecommended(0) {}

    inline const QString& getLongName() const { return longName; }
    inline bool hasParent() const { return parent != ""; }

    //! Retourne le parent de la formation, lève une exception s’il n’existe pas
    inline const Formation& getParent() const { return FM->getItem(parent); }

    inline const std::map<CategorieUV, int>& getRequirements() const { return requirements; }
    inline unsigned int getLignesTSH() const { return nbLignes; }
    inline unsigned int getColonnesTSH() const { return nbColonnes; }

    inline bool hasChildren() const {
        std::vector<Formation> formations = FM->iterator();
        for(auto it=formations.begin(); it!=formations.end(); it++) {
            if (it->hasParent() && (it->getParent() == *this)) {
                return true;
            }
        }
        return false;
    }

    inline void setLongName(const QString &l) { longName = l; }
    inline void setRequirements(const QString &c, unsigned int n) {
        //Vérifie si la catégorie existe
        CategorieUV cat("", "");
        try {
            cat = CUM->getItem(c);
        } catch (Exception) {
            return;
        }

        requirements[cat] = n;
    }

    inline void setParent(const QString& p) {
        //On vérifie que le parent existe
        try {
            FM->getItem(p);
        } catch (Exception) {
            return;
        }

        parent = p;
    }
    inline void setLignesTSH(unsigned int l) { nbLignes = l; }
    inline void setColonnesTSH(unsigned int c) { nbColonnes = c; }

  protected:
    QString longName;

    //! Formation parente, vide si pas de parent
    QString parent;

    //! Minimums de crédits requis par catégories
    std::map<CategorieUV, int> requirements;

    //! UVs dont la validation est nécessaire
    std::vector<Uv> compulsory;

    //! UVs dont la validation est recommandée
    std::vector<Uv> recommended;

    //! Nombre de lignes présentes dans le tableau TSH
    unsigned int nbLignes;

    //! Nombre de colonnes présentes dans le tableau TSH
    unsigned int nbColonnes;

    //! Nombre minimum de crédits à valider toutes catégories confondues
    unsigned int minCredits;

    //! Nombre minimum d’UV à valider dans les UVs recommandées
    unsigned int minNbUvRecommended;

};

#endif // FORMATION_HPP
