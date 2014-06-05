#ifndef FORMATION_HPP
#define FORMATION_HPP 1

#include <QString>
#include <map>
#include "structures.hpp"

#define CUM CategorieUVManager::getInstance()

//! Classe des Formations
class Formation {

  public:

    Formation(const QString& abbr, const QString& n) : abbreviation(abbr), nom(n) {}

    inline const QString& getNom() const { return nom; }
    inline const QString& getAbbreviation() const { return abbreviation; }
    inline const std::map<QString, int>& getRequirements() const { return requirements; }

    inline void setNom(const QString &n) { nom = n; }
    inline void setAbbreviation(const QString &a) { abbreviation = a; }
    inline void setRequirements(const QString &c, unsigned int n) {
        //Vérifie si la catégorie existe
        CUM->getItem(c);
        requirements[c] = n;
    }

  protected:
    QString abbreviation;
    QString nom;

    //! Minimums de crédits requis par catégories
    std::map<QString, int> requirements;

    //! UVs dont la validation est nécessaire
    std::vector<QString> compulsory;

    //! UVs dont la validation est recommandée
    std::vector<QString> recommended;

    //! Nombre minimum d’UV à valider dans les UVs recommandées
    unsigned int minRecommended;

};


#endif // FORMATION_HPP
