#ifndef STRUCTURES_H
#define STRUCTURES_H 1

#include <QString>
#include "manager.hpp"
#include "singleton.hpp"

//! Structure représentant un semestre temporel
struct SemestreT {

    //! Constructeur, prend en argument une QString ex: "A12"
    SemestreT(const QString& s) {
        representation = s;
        isPrintemps = s.startsWith('P');
        annee = 2000 + s.left(1).toInt();
    }

    //! Représentation du semestre ex: "A12"
    QString representation;
    //! Année du semestre ex: 2012
    unsigned int annee;
    //! Indique le semestre de l’année ex: false
    bool isPrintemps;

    //! Opérateur d’égalité pour ordonner les semestres
    inline bool operator==(const SemestreT &s) const {
        return (annee == s.annee) && (isPrintemps == s.isPrintemps);
    }

    //! Opérateur de comparaison pour ordonner les semestres
    inline bool operator<(const SemestreT &s) const {
        if (*this == s) {
            return false;
        } else {
            if (annee < s.annee) { return true; }
            if (!isPrintemps) { return true; }
            return false;
        }
    }


};

//! Structure définissant les catégories d'UV
struct CategorieUV {
  //! Nom de la catégorie
  QString nom;

  //! Abbréviation de la catégorie
  QString abbreviation;

};

//! Structure définissant les notes obtenues aux UVs
struct NoteUV {
  //! Note obtenue (A, B, C, ...)
  QString nom;

  //! Booléen indiquant la réussite de l'UV
  bool reussite;
};

typedef Singleton<Manager<CategorieUV>> CategorieUVManager;

#endif // STRUCTURES_H
