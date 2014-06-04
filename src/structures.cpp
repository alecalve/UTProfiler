#include "structures.hpp"
#include "exceptions.hpp"

template<>
CategorieUV& Manager<CategorieUV>::getItem(const QString &s) const {
    int index = -1;
    for (auto it=elements.begin(); it!=elements.end(); it++) {
        if (it->nom == s) {
            index++;
            CategorieUV& cat = const_cast<CategorieUV&>(elements.at(index));
            return cat;
        }
    }

    throw Exception("Catégorie non trouvée.");
}

