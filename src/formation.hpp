#ifndef FORMATION_HPP
#define FORMATION_HPP 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "singleton.hpp"
#include "manager.hpp"
#include "uvmanager.hpp"

#include <iostream>

#define CUM CategorieUVManager::getInstance()
#define UVM UvManager::getInstance()

//! Classe des Formations
class Formation : public BaseItem {

  public:

    Formation(const QString& abbr, const QString& n)
        : BaseItem(abbr), longName(n), parent(0), nbLignes(0), nbColonnes(0),
          minCredits(0), minNbUvRecommended(0) {}

    inline const QString& getLongName() const { return longName; }
    inline const Formation* getParent() const { return parent; }
    inline const std::map<CategorieUV, int>& getRequirements() const { return requirements; }
    inline unsigned int getLignesTSH() const { return nbLignes; }
    inline unsigned int getColonnesTSH() const { return nbColonnes; }

    inline void setLongName(const QString &l) { longName = l; }
    inline void setRequirements(const QString &c, unsigned int n) {
        //Vérifie si la catégorie existe
        CategorieUV cat = CUM->getItem(c);
        requirements[cat] = n;
    }

    inline void setLignesTSH(unsigned int l) { nbLignes = l; }
    inline void setColonnesTSH(unsigned int c) { nbColonnes = c; }

  protected:
    QString longName;

    //! Formation parente, vide si pas de parent
    Formation* parent;

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


typedef Singleton<Manager<Formation>> FormationManager;

#endif // FORMATION_HPP
