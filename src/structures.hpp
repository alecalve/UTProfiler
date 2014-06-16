#ifndef STRUCTURES_H
#define STRUCTURES_H 1

#include <QString>
#include "manager.hpp"
#include "singleton.hpp"

//! Structure représentant un semestre temporel
struct SemestreT {

    //! Constructeur par défaut
    SemestreT() {}

    //! Constructeur, prend en argument une QString ex: "A12"
    SemestreT(const QString& s) {
        representation = s;
        isPrintemps = s.startsWith('P');
        annee = 2000 + s.right(2).toInt();
    }

    //! Constructeur, prend en argument une année et un caractère
    SemestreT(QString c, unsigned int a) {
        representation = c.append(QString::number(a).right(2));
        isPrintemps = c.startsWith('P');
        annee = a;
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

    //! Constructeur de base, prend en argumunt l’abbréviation de la catégorie et son nom complet
    CategorieUV(const QString& n, const QString& l) : BaseItem(n), longName(l) {}

    //! Renvoie le nom complet de la catégorie
    const QString getLongName() const { return longName; }

    //! Met à jour le nom complet de la catégorie
    void setLongName(const QString& l) { longName = l; }

  private:

    //! Nom développé de la catégorie
    QString longName;

};

//! Classe définissant les notes obtenues aux UVs
class NoteUV : public BaseItem {

  public:

    //! Constructeur de base, prend en argumunt la note et si elle fait réussir l’UV
    NoteUV(const QString& n, bool r): BaseItem(n), reussite(r) {}

    //! Indique si cette note fait réussir une UV
    bool getReussite() { return reussite; }

    //! Utilisé pour indiquer si cette note fait réussir une UV
    void setReussite(bool r) { reussite = r; }

  private:

    //! Booléen indiquant la réussite de l'UV
    bool reussite;

};

//! Manager de CatégorieUV
typedef Singleton<Manager<CategorieUV>> CategorieUVManager;

//! Manager de NoteUV
typedef Singleton<Manager<NoteUV>> NoteUVManager;

#endif // STRUCTURES_H
