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

//! Classe définissant les catégories d'UV
class CategorieUV : public BaseItem {

  public:
    CategorieUV(const QString& n, const QString& a) : BaseItem(n), abbreviation(a) {}

    const QString getAbbreviation() const { return abbreviation; }
    void setAbbreviation(const QString& a) { abbreviation = a; }

  private:
    //! Abbréviation de la catégorie
    QString abbreviation;

};

//! Classe définissant les notes obtenues aux UVs
class NoteUV : public BaseItem {

  public:
    NoteUV(const QString& n, bool r): BaseItem(n), reussite(r) {}

    bool getReussite() { return reussite; }
    void setReussite(bool r) { reussite = r; }

  private:
    //! Booléen indiquant la réussite de l'UV
    bool reussite;

};

typedef Singleton<Manager<CategorieUV>> CategorieUVManager;
typedef Singleton<Manager<NoteUV>> NoteUVManager;

#endif // STRUCTURES_H
