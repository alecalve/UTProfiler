#ifndef XMLIO_HPP
#define XMLIO_HPP 1

#include <QtXml>
#include <QFile>
#include <QString>
#include <vector>

#include "abstractio.hpp"
#include "uvmanager.hpp"
#include "structures.hpp"
#include "formation.hpp"

//! Implémentation de AbstractIo pour les exports XML
class XmlIo : public AbstractIo {

  public:
    //! Fonction pour le chargement et la sauvegarde de fichier XML contenant les infos sur l'université
    void load();
    void save();
  private:
    //! variable contenant le nom d'un document
    QDomDocument document;

};


#endif // XMLIO_HPP
