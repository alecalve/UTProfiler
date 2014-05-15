#include "uvmanager.hpp"

#include "exceptions.hpp"

template<>
const Uv& Manager<Uv>::getItem(const std::string &s) const {
   for (auto it=elements.begin(); it!=elements.end(); it++) {
        if (it->getCode() == s) {
            return *it;
        }
    }

   throw ItemNotFoundException();
}
