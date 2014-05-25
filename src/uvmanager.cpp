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

    throw Exception("objet non trouvé.");
}


//! Ajout d'Uv, Mais je suis pas certain du truc car je comprends pas si on a un tableau d'UV (uvs)dans notre Uv manager.
//! Il faudrait que j'ajoute des variables nbMaxUv et nbUv dans notre classe Uvmanager mais je crois qu'on a déja qqch.
template<>
void Manager<Uv>::addItem(Uv* uv) {
    if (nbMaxUv==nbUv){//agrandir le tableau d'Uvs
        Uv** tmp=new Uv* [nbMaxUv+10];
        memcpy(tmp,uvs,sizeof(Uv*)*nbUv);
        Uv** old=uvs;
        uvs=tmp;
        nbMaxUV+=10;
        delete[] old;
            }
            uvs[nbUv++]=uv;
        }

//! Suppression d'une Uv, meme probleme il faudrait que j'ajoute un tableau d'uvs, le nbMaxUv et le nbUv
//! dans notre uvmanager. C'est possible ?
template<>
void Manager<Uv>::suppression(Qstring c) {
    for (unsigned int i=0;i<nbMaxUv;++i){
        if (uvs[i]->code==c) {
            delete uvs[i];
            nbUv--;
        }
        else throw Exception("UV "+c+" inexistante");
    }
}
