#ifndef STRUCTURES_H
#define STRUCTURES_H 1

#include <string>

struct CategorieUV {
  std::string nom;

  inline bool operator<(const CategorieUV &cat) const{
    return this->nom < cat.nom;
  }

};

struct NoteUV {
  std::string nom;
  bool reussite;
};

#endif // STRUCTURES_H
