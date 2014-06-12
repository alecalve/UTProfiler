#ifndef ABSTRACTIO_HPP
#define ABSTRACTIO_HPP 1

#include <vector>
#include <QString>

//! Classe abstraite gérant les exports et imports
class AbstractIo {

  public:
    AbstractIo() {}
    AbstractIo(const QString &s): identifier(s) {}

    void setIdentifier(const QString &s) { identifier = s; }
    const QString& getIdentifier() { return identifier; }

    //! Rempli les managers des données sauvegardées
    virtual void load()=0;

    //! Écrit une sauvegarde des données des managers
    virtual void save()=0;
    virtual ~AbstractIo() {}

  protected:
    //! Identifiant de la sauvegarde (fichier, etc ..)
    QString identifier;

};

#endif // ABSTRACTIO_HPP
