#ifndef UV_H
#define UV_H 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "manager.hpp"

//! Classe des UV
class Uv : public BaseItem {


    //! Les fonctions getXXXX servent à recuperer l'attribut XXXX de l'UV, et les fonctions setXXX servent à définir les
    //! attributs, la fonction resetCrédits sert à remettre les crédits donnés par l'UV à 0 dans toutes les catégories
    //! la fonction operator== permet de comparer le code de 2 uvs et renvoie vrai si ils sont égaux et faux dans le cas contraire
  public:

    Uv() : BaseItem("") {}

    //! Constructeur par défaut, met les ouvertures printemps et automne à false, Appel le constructeur de la classe mère
    //! BaseItem, et initialise le code et la description avec les paramètres d'entrées
    Uv(QString c, QString d) : BaseItem(c), code(c), description(d) {
        ouvertureAutomne = false;
        ouverturePrintemps = false;
        name = code;
    }
    inline const QString& getCode() const { return code; }
    inline const QString& getDescription() const { return description; }
    inline bool getOuvertureAutomne() const { return ouvertureAutomne; }
    inline bool getOuverturePrintemps() const { return ouverturePrintemps; }
    unsigned int getCredits() const;
    inline const std::map<QString, unsigned int>& getRecompenses() const { return recompenses; }

    inline void setCode(const QString &c) { code = c; }
    inline void setOuverturePrintemps(const bool &b) { ouverturePrintemps = b; }
    inline void setOuvertureAutomne(const bool &b) { ouvertureAutomne = b; }
    inline void setDescription(const QString &d) { description = d; }
    inline void setCredits(const QString cat, const unsigned int creds) { recompenses[cat] = creds; }
    inline void resetCredits() { recompenses.clear(); }
    inline bool operator==(const Uv& u) { return (u.getCode() == code); }

    //! Attribut du code de l'uv, sa description, son tableau des recompenses avec le nombre
    //! de crédit pour les differentes catégories, les attributs ouvertureAutomne/Printemps définissent
    //! si l'uv est ouverte au semestre d'Automne/Printemps
  private:
    QString code;
    QString description;
    std::map<QString, unsigned int> recompenses;
    bool ouvertureAutomne;
    bool ouverturePrintemps;

};

#endif // UV_H
