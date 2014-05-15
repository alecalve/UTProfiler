#ifndef UV_H
#define UV_H 1

#include <string.h>
#include <map>

#include "structures.hpp"

//! Classe des UV
class Uv {

  public:
    Uv(std::string c, std::string d) : code(c), description(d) {
        ouvertureAutomne = false;
        ouverturePrintemps = false;
    }

    inline const std::string& getCode() const { return code; }
    inline const std::string& getDescription() const { return description; }
    inline bool getOuvertureAutomne() const { return ouvertureAutomne; }
    inline bool getOuverturePrintemps() const { return ouverturePrintemps; }
    unsigned int getCredits() const;

    inline void setCode(const std::string &c) { code = c; }
    inline void setOuverturePrintemps(const bool &b) { ouverturePrintemps = b; }
    inline void setOuvertureAutomne(const bool &b) { ouvertureAutomne = b; }
    inline void setDescription(const std::string &d) { description = d; }
    inline void setCredits(const CategorieUV &cat, const unsigned int &creds) { recompenses[cat] = creds; }

  private:
    std::string code;
    std::string description;
    std::map<CategorieUV, unsigned int> recompenses;
    bool ouvertureAutomne;
    bool ouverturePrintemps;

};

#endif // UV_H
