#include "formation.hpp"

template<>
void Manager<Formation>::suppItem(const QString &s) {
    //On ne supprime pas de formation si elle a des enfants
    try {
        Formation item = FM->getItem(s);
        if (item.hasChildren()) {
            return;
        } else {
            bool found = false;

            for(auto it=elements.begin(); !found && it!=elements.end(); it++) {
                if (*it == item) {
                    //On met it = devant pour ne pas invalider l’iterateur
                    //Sinon si on supprime des élements pendant une itération
                    //sans mettre à jour l’itérateur il se passe n’importe quoi
                    it = elements.erase(it);
                    found = true;
                }
            }
        }
    } catch (Exception) {
        return;
    }
}
