#ifndef ABSTRACTIO_HPP
#define ABSTRACTIO_HPP 1

#include <vector>
#include <QString>

#include "uv.hpp"

//! Classe abstraite gérant les exports et imports
class AbstractIo {

  public:
    AbstractIo(const QString &s): identifier(s) {}

    void setIdentifier(const QString &s) { identifier = s; }
    const QString& getIdentifier() { return identifier; }

    //! Renvoie la liste des UVs présentent dans la sauvegarde
    virtual std::vector<Uv> load()=0;

    //! Écrit une sauvegarde avec les UVs fournies en argument
    virtual void save(std::vector<Uv>)=0;
    virtual ~AbstractIo() {}

  protected:
    //! Identifiant de la sauvegarde (fichier, etc ..)
    QString identifier;

};

#endif // ABSTRACTIO_HPP
