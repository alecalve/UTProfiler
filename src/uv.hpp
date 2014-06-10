#ifndef UV_H
#define UV_H 1

#include <QString>
#include <map>

#include "structures.hpp"
#include "manager.hpp"

//! Classe des UV
class Uv : public BaseItem {

  public:

    Uv() : BaseItem("") {}

    //! Constructeur par défaut, met les ouvertures printemps et automne à false
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

  private:
    QString code;
    QString description;
    std::map<QString, unsigned int> recompenses;
    bool ouvertureAutomne;
    bool ouverturePrintemps;

};

#endif // UV_H
