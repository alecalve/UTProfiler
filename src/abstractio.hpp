#ifndef ABSTRACTIO_HPP
#define ABSTRACTIO_HPP 1

#include <vector>
#include <QString>

//! Classe abstraite gérant les exports et imports
class AbstractIo {

  public:
    //! Constructeur par défaut
    AbstractIo() {}

    //! Constructeur de base, prend en argument l’identifiant de la ressource (URL, nom de fichier, …)
    AbstractIo(const QString &s): identifier(s) {}

    //! Met à jour l’identifiant de la ressource (URL, nom de fichier, …)
    void setIdentifier(const QString &s) { identifier = s; }

    //! Renvoie l’identifiant de la ressource (URL, nom de fichier, …)
    const QString& getIdentifier() { return identifier; }

    //! Rempli les managers des données sauvegardées
    virtual void load()=0;

    //! Écrit une sauvegarde des données des managers
    virtual void save()=0;

    //! Destructeur, ne fait rien
    virtual ~AbstractIo() {}

  protected:
    //! Identifiant de la sauvegarde (fichier, etc ..)
    QString identifier;

};

#endif // ABSTRACTIO_HPP
