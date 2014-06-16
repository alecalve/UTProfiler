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


//! Classe représentant un dossier d’un étudiant
class Dossier : public BaseItem {

  public:

    //! Constructeur par défaut
    Dossier() : BaseItem() {}

    //! Constructeur basique, prend en argument le login de l’étudiant
    Dossier(const QString& l) : BaseItem(l) {}

    //! Indique si l’activité extrascolaire a été complétée ou non
    inline void setExtraScolaire(const bool& a) { extraScolaire = a; }

    //! Ajoute un semestre d’étude au dossier
    inline void addSemestre(const Semestre& s) { semestres.push_back(s); }

    //! Ajoute une équivalence de crédits au dossier
    inline void addEquivalence(const Equivalence& e) { equivalences.push_back(e); }

    //! Ajoute une formation suivie au dossier
    inline void addFormation(const Formation& f) { formations.push_back(f); }

    //! Enlève une formation suivie du dossier
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

    //! Enlève une équivalence, identifiée par son nom, du dossier
    inline void removeEquivalence(QString e) {
        bool found = false;
        for(auto it=equivalences.begin(); !found && it!=equivalences.end(); it++) {
            if (it->getName() == e) {
                it = equivalences.erase(it);
                found = true;
            }
        }
    }

    //! Supprime du dossier un semestre d’étude, identifié par son nom (ex: TC01)
    inline void removeSemestre(QString s) {
        bool found = false;
        for(auto it=semestres.begin(); !found && it!=semestres.end(); it++) {
            if (it->getName() == s) {
                it = semestres.erase(it);
                found = true;
            }
        }
    }

    //! Retourne les semestres du dossier
    inline const std::vector<Semestre>& getSemestres() { return semestres; }

    //! Retourne si l’activité extrascolaire a été effectuée
    inline bool getExtraScolaire() { return extraScolaire; }

    //! Retourne les équivalences du dossier
    inline const std::vector<Equivalence>& getEquivalences() { return equivalences; }

    //! Retourne les formations du dossier
    inline const std::vector<Formation>& getFormations() { return formations; }

    //! Retourne une QStringList des noms des formations suivies par l’étudiant
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

//! Manager des Dossiers
typedef Singleton<Manager<Dossier>> DossierManager;

#endif // DOSSIER_HPP
