#include "uvmanager.hpp"

#include "exceptions.hpp"

template<>
Uv& Manager<Uv>::getItem(const QString &s) const {
    int index = -1;
    for (auto it=elements.begin(); it!=elements.end(); it++) {
        index++;
        if (it->getCode() == s) {
            Uv& u = const_cast<Uv&>(elements.at(index));
            return u;
        }
    }

    throw Exception("UV non trouvée.");
}
