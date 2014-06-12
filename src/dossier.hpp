#ifndef DOSSIER_HPP
#define DOSSIER_HPP 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "formation.hpp"
#include "semestre.hpp"
#include "singleton.hpp"
#include "manager.hpp"

#define FM FormationManager::getInstance()


class Dossier : public BaseItem {

  public:
    Dossier(const QString& l) : BaseItem(l) {}

    inline void setExtraScolaire(const bool& a) { extraScolaire = a; }
    inline void addSemestre(const Semestre& s) { semestres.push_back(s); }
    inline void addFormation(const Formation& f) {
        formations.push_back(f);
    }

    inline const std::vector<Semestre>& getSemestres() { return semestres; }
    inline bool getExtraScolaire() { return extraScolaire; }
    inline const std::vector<Formation>& getFormations() { return formations; }

  private:
    //! Semestres suivis
    std::vector<Semestre> semestres;

    //! Activité extra-scolaire validée
    bool extraScolaire;

    //! Niveaux de langues ex: "Anglais" => "C1"
    std::map<QString, QString> langues;

    //! Formations suivies (pas forcément validées)
    std::vector<Formation> formations;
};

typedef Singleton<Manager<Dossier>> DossierManager;

#endif // DOSSIER_HPP
