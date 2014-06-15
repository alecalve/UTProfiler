#ifndef EQUIVALENCE_HPP
#define EQUIVALENCE_HPP

#include <map>

#include "structures.hpp"

#define CUM CategorieUVManager::getInstance()

class Equivalence : public BaseItem {

  public:
    Equivalence() : BaseItem() {}
    Equivalence(const QString& n, const QString& e) : BaseItem(n), explication(e) {}

    inline const QString& getExplication() const { return explication; }
    inline const std::map<CategorieUV, unsigned int>& getCredits() const { return credits; }
    inline const SemestreT& getSemestre() const { return semestre; }

    inline void setSemestre(const SemestreT& s) { semestre = s; }
    inline void setExplication(const QString& e) { explication = e; }
    inline void setCredits(CategorieUV& cat, unsigned int c) { credits[cat] = c; }
    inline void setCredits(const QString& cat, unsigned int c) {
        CategorieUV categorie = CUM->getItem(cat);
        credits[categorie] = c;
    }

  private:
    std::map<CategorieUV, unsigned int> credits;
    QString explication;
    SemestreT semestre;

};

#endif // EQUIVALENCE_HPP
