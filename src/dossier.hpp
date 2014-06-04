#ifndef DOSSIER_HPP
#define DOSSIER_HPP 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "formation.hpp"
#include "semestre.hpp"

class Dossier {

  public:
    Dossier(const QString& l) : login(l) {}

    inline void setLogin(const QString& l) {login = l; }
    inline void setExtraScolaire(const bool& a) { extraScolaire = a; }
    inline void addSemestre(const Semestre& s) { semestres.push_back(s); }

    inline const std::vector<Semestre>& getSemestres() { return semestres; }
    inline bool getExtraScolaire() { return extraScolaire; }
    inline const QString& getLogin() { return login; }

  private:
    //! Login de la personne à qui appartient ce dossier
    QString login;

    //! Semestres suivis
    std::vector<Semestre> semestres;

    //! Activité extra-scolaire validée
    bool extraScolaire;

    //! Niveaux de langues ex: "Anglais" => "C1"
    std::map<QString, QString> langues;

    //! Formations suivies (pas forcément validées)
    std::vector<Formation> formations;
};

#endif // DOSSIER_HPP
