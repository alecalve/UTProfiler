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

    //! Constructeur par défaut
    Formation() {}

    //! Constructeur de base, prend en arguments l’abbréviation et le nom détaillé de la formation
    Formation(const QString& abbr, const QString& n)
        : BaseItem(abbr), longName(n), parent(""), minCredits(0) {}

    //! Renvoie le nombre minimum de crédits à avoir
    inline unsigned int getMinCredits() const { return minCredits; }

    //! Met à jour le nombre minimum de crédits à avoir
    inline void setMinCredits(unsigned int c) { minCredits = c; }

    //! Renvoie le nom détaillé de la formation
    inline const QString& getLongName() const { return longName; }

    //! Indique si la formation a une formation parente
    inline bool hasParent() const { return parent != ""; }

    //! Ajoute une UV aux UVs proposées par la formation
    inline void addUv(const QString& u) { uvs.push_back(UVM->getItem(u)); }

    //! Ajoute une UV aux UVs proposées par la formation
    inline void addUv(Uv u) { uvs.push_back(u); }

    //! Retourne le parent de la formation, lève une exception s’il n’existe pas
    inline const Formation& getParent() const { return FM->getItem(parent); }

    //! Retourne les crédits minimums requis par catégories
    inline const std::map<CategorieUV, int>& getRequirements() const { return requirements; }

    //! Retourne les UVs proposées à la formation
    inline const std::vector<Uv>& getUvs() const { return uvs; }

    //! Vide la liste des UVs
    inline void resetUVs() { uvs.clear(); std::cout<<uvs.size()<<std::endl; }

    //! Indique si cette formation a au moins un enfant
    inline bool hasChildren() const {
        std::vector<Formation> formations = FM->iterator();
        for(auto it=formations.begin(); it!=formations.end(); it++) {
            if (it->hasParent() && (it->getParent() == *this)) {
                return true;
            }
        }
        return false;
    }

    //! Met à jour le nom détaillé de la formation
    inline void setLongName(const QString &l) { longName = l; }

    //! Met à jour un nombre minimum de crédits pour une catégorie
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

    //! Indique le parent de la formation, ne se passe rien si le parent n’existe pas
    inline void setParent(const QString& p) {
        //On vérifie que le parent existe
        try {
            FM->getItem(p);
        } catch (Exception) {
            return;
        }

        parent = p;
    }

  protected:

    //! Nom détaillé de la formation
    QString longName;

    //! Formation parente, vide si pas de parent
    QString parent;

    //! Minimums de crédits requis par catégories
    std::map<CategorieUV, int> requirements;

    //! UVs de la formation
    std::vector<Uv> uvs;

    //! Nombre minimum de crédits à valider toutes catégories confondues
    unsigned int minCredits;


};

#endif // FORMATION_HPP
