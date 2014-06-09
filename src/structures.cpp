#include "structures.hpp"
#include "exceptions.hpp"

template<>
CategorieUV& Manager<CategorieUV>::getItem(const QString &s) const {
    int index = -1;
    for (auto it=elements.begin(); it!=elements.end(); it++) {
        index++;
        if (it->nom == s) {
            CategorieUV& cat = const_cast<CategorieUV&>(elements.at(index));
            return cat;
        }
    }

    throw Exception("Catégorie non trouvée.");
}

template<>
NoteUV& Manager<NoteUV>::getItem(const QString &s) const {
    int index = -1;
    std::cout<<"searching for "<<s.toStdString()<<std::endl;
    for (auto it=elements.begin(); it!=elements.end(); it++) {
        index++;
        if (it->nom == s) {

            std::cout<<it->nom.toStdString()<<"=="<<s.toStdString()<<" donne "<<(it->nom==s)<<" at "<<index<<std::endl;
            NoteUV& cat = const_cast<NoteUV&>(elements.at(index));
            std::cout<<"found at "<<index<<" "<<cat.nom.toStdString()<<std::endl;
            return cat;
        }
    }

    throw Exception("Note non trouvée.");
}

