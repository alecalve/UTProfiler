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
    Semestre(const QString& s) : BaseItem(s) {}
    inline void setSemestre(SemestreT s) { semestre = s; }
    inline void setFormation(Formation f) { formationSuivie = f; }
    inline void setResultat(const QString& u, const QString& r) { resultats[u] = r; }

    inline const SemestreT& getSemestre() const { return semestre; }
    inline const Formation& getFormation() const { return formationSuivie; }
    inline const std::map<QString, QString>& getResultats() const { return resultats; }

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

