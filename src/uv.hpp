#ifndef UV_H
#define UV_H 1

#include <QString>
#include <map>

#include "structures.hpp"

//! Classe des UV
class Uv {

  public:
    Uv(QString c, QString d) : code(c), description(d) {
        ouvertureAutomne = false;
        ouverturePrintemps = false;
    }

    inline const QString& getCode() const { return code; }
    inline const QString& getDescription() const { return description; }
    inline bool getOuvertureAutomne() const { return ouvertureAutomne; }
    inline bool getOuverturePrintemps() const { return ouverturePrintemps; }
    unsigned int getCredits() const;

    inline void setCode(const QString &c) { code = c; }
    inline void setOuverturePrintemps(const bool &b) { ouverturePrintemps = b; }
    inline void setOuvertureAutomne(const bool &b) { ouvertureAutomne = b; }
    inline void setDescription(const QString &d) { description = d; }
    inline void setCredits(const CategorieUV &cat, const unsigned int &creds) { recompenses[cat] = creds; }

  private:
    QString code;
    QString description;
    std::map<CategorieUV, unsigned int> recompenses;
    bool ouvertureAutomne;
    bool ouverturePrintemps;

};

#endif // UV_H
