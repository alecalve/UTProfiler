#ifndef STRUCTURES_H
#define STRUCTURES_H 1

#include <string>

//! Structure définissant les catégories d'UV
struct CategorieUV {
  //! Nom de la catégorie
  std::string nom;

  //! Opérateur de comparaison nécessaire pour l'usage dans un map
  inline bool operator<(const CategorieUV &cat) const {
    return this->nom < cat.nom;
  }

};

//! Structure définissant les notes obtenues aux UVs
struct NoteUV {
  //! Note obtenue (A, B, C, ...)
  std::string nom;

  //! Booléen indiquant la réussite de l'UV
  bool reussite;
};

#endif // STRUCTURES_H
