#ifndef UV_H
#define UV_H 1

#include <string.h>
#include <map>

#include "structures.hpp"

class Uv {

  public:
    Uv(std::string c, std::string d) : code(c), description(d) {}

    inline const std::string& getCode() const { return code; }
    inline const std::string& getDescription() const { return description; }
    unsigned int getCredits() const;

    inline void setCode(std::string c) { code = c; }
    inline void setDescription(std::string d) { description = d; }
    inline void setCredits(CategorieUV cat, unsigned int creds) { recompenses[cat] = creds; }


  private:
    std::string code;
    std::string description;
    std::map<CategorieUV, unsigned int> recompenses;

    Uv(const Uv&);
    Uv operator=(const Uv&);

};

#endif // UV_H
