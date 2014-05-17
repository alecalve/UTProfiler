#include "uvmanager.hpp"

#include "exceptions.hpp"

template<>
const Uv& Manager<Uv>::getItem(const QString &s) const {
   for (auto it=elements.begin(); it!=elements.end(); it++) {
        if (it->getCode() == s) {
            return *it;
        }
    }

   throw Exception("objet non trouvé.");
}
