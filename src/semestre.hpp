#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP 1

#include <QString>
#include <map>
#include "structures.hpp"

//! Représente un semestre d´étude
class Semestre {

  public:
    inline void setSemestre(const QString& s) { semestre = SemestreT(s); }
    inline const SemestreT& getSemestre() const { return semestre; }

    inline const std::map<QString, NoteUV>& getResultats() const { return resultats; }

  private:
    //! Semestre du semestre
    SemestreT semestre;

    //! Lien entre les uvs suivies et leurs résultats
    std::map<QString, NoteUV> resultats;

};

#endif // SEMESTRE_HPP

