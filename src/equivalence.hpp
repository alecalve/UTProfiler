#ifndef EQUIVALENCE_HPP
#define EQUIVALENCE_HPP

#include <map>

#include "structures.hpp"

#define CUM CategorieUVManager::getInstance()


//! Décrit une équivalence de crédits (formation antérieure, semestre à l’étranger)
class Equivalence : public BaseItem {

  public:

    //! Constructeur par défaut
    Equivalence() : BaseItem() {}

    //! Constructeur par défaut, prend en argument le nom de l’équivalence et une explication de celle-ci
    Equivalence(const QString& n, const QString& e) : BaseItem(n), explication(e) {}

    //! Retourne l’explication de l’équivalence
    inline const QString& getExplication() const { return explication; }

    //! Renvoie les équivalences de crédits reçues
    inline const std::map<CategorieUV, unsigned int>& getCredits() const { return credits; }

    //! Retourne le semestre de l’équivalence
    inline const SemestreT& getSemestre() const { return semestre; }

    //! Met à jour le semestre de l’équivalence
    inline void setSemestre(const SemestreT& s) { semestre = s; }

    //! Met à jour l’explication de l’équivalence
    inline void setExplication(const QString& e) { explication = e; }

    //! Ajoute une équivalence de crédits pour une certaine catégorie
    inline void setCredits(CategorieUV& cat, unsigned int c) { credits[cat] = c; }

    //! Ajoute une équivalence de crédits pour une certaine catégorie
    inline void setCredits(const QString& cat, unsigned int c) {
        CategorieUV categorie = CUM->getItem(cat);
        credits[categorie] = c;
    }

    //! Retourne une QStringList décrivant les équivalences (ex: {"12 CS", "24 TSH"})
    inline QStringList getCreditsList() const {
        QStringList ret;
        for(auto it=credits.begin(); it!=credits.end(); it++) {
            QStringList temp;
            temp << QString::number(it->second) << " " << it->first.getName();
            ret << temp.join(" ");
        }
        return ret;
    }

  private:

    //! Équivalences de crédits
    std::map<CategorieUV, unsigned int> credits;

    //! Explication de l’équivalence
    QString explication;

    //! Semestre de l’équivalence
    SemestreT semestre;

};

#endif // EQUIVALENCE_HPP
