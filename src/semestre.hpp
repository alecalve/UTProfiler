#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP 1

#include <QString>
#include <map>
#include "structures.hpp"
#include "manager.hpp"
#include "formation.hpp"

//! Représente un semestre d´étude
class Semestre : public BaseItem {

  public:
    //! Constructeur de base, prend en argument le nom du semestre (ex: TC01)
    Semestre(const QString& s) : BaseItem(s) {}

    //! Met à jour le SemetreT du Semestre (ex: A12)
    inline void setSemestre(SemestreT s) { semestre = s; }

    //! Met à jour la formation suivie lors du semestre
    inline void setFormation(Formation f) { formationSuivie = f; }

    //! Met à jour le résultat d’une UV
    inline void setResultat(const QString& u, const QString& r) { resultats[u] = r; }

    //! Renvoie le SemestreT du semestre d’étude
    inline const SemestreT& getSemestre() const { return semestre; }

    //! Renvoie la formation suivie lors du semestre d’étude
    inline const Formation& getFormation() const { return formationSuivie; }

    //! Renvoie une map Uv(nom) => NoteUV(nom) des résultats obtenus lors du semestre
    inline const std::map<QString, QString>& getResultats() const { return resultats; }

    //! Renvoie la liste des noms et notes des UV suivies lors du semestre
    inline QStringList getUvList() const {
        QStringList ret;
        for(auto it=resultats.begin(); it!=resultats.end(); it++) {
            QStringList temp;
            temp << it->first << "(" << it->second << ")";
            ret << temp.join("");
        }
        return ret;
    }

  private:
    //! Semestre du semestre
    SemestreT semestre;

    //! Formation suivie lors du semestre
    Formation formationSuivie;

    //! Lien entre les uvs suivies et leurs résultats
    std::map<QString, QString> resultats;

};

#endif // SEMESTRE_HPP

