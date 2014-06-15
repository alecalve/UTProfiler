#ifndef DOSSIER_HPP
#define DOSSIER_HPP 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "formation.hpp"
#include "semestre.hpp"
#include "singleton.hpp"
#include "manager.hpp"
#include "equivalence.hpp"

#define FM FormationManager::getInstance()


class Dossier : public BaseItem {

  public:
    Dossier() : BaseItem() {}
    Dossier(const QString& l) : BaseItem(l) {}
    inline void setExtraScolaire(const bool& a) { extraScolaire = a; }
    inline void addSemestre(const Semestre& s) { semestres.push_back(s); }
    inline void addEquivalence(const Equivalence& e) { equivalences.push_back(e); }
    inline void addFormation(const Formation& f) { formations.push_back(f); }

    inline void removeFormation(QString f) {
        Formation form = FM->getItem(f);
        bool found = false;
        for(auto it=formations.begin(); !found && it!=formations.end(); it++) {
            if (*it == form) {
                it = formations.erase(it);
                found = true;
            }
        }
    }

    inline void removeEquivalence(QString e) {
        bool found = false;
        for(auto it=equivalences.begin(); !found && it!=equivalences.end(); it++) {
            if (it->getName() == e) {
                it = equivalences.erase(it);
                found = true;
            }
        }
    }

    inline void removeSemestre(QString s) {
        bool found = false;
        for(auto it=semestres.begin(); !found && it!=semestres.end(); it++) {
            if (it->getName() == s) {
                it = semestres.erase(it);
                found = true;
            }
        }
    }

    inline const std::vector<Semestre>& getSemestres() { return semestres; }
    inline bool getExtraScolaire() { return extraScolaire; }
    inline const std::vector<Equivalence>& getEquivalences() { return equivalences; }
    inline const std::vector<Formation>& getFormations() { return formations; }
    inline const QStringList getFormationsName() {
        QStringList list;
        for(auto it=formations.begin(); it!=formations.end(); it++) {
            list << it->getName();
        }
        return list;
    }

  private:
    //! Semestres suivis
    std::vector<Semestre> semestres;

    //! Équivalences eues
    std::vector<Equivalence> equivalences;

    //! Activité extra-scolaire validée
    bool extraScolaire;

    //! Formations suivies (pas forcément validées)
    std::vector<Formation> formations;
};

typedef Singleton<Manager<Dossier>> DossierManager;

#endif // DOSSIER_HPP
