#ifndef XMLIO_HPP
#define XMLIO_HPP 1

#include <QtXml>
#include <QFile>
#include <QString>
#include <vector>

#include "abstractio.hpp"
#include "uvmanager.hpp"

//! Implémentation de AbstractIo pour les exports XML
class XmlIo : public AbstractIo {

  public:
    XmlIo(const QString &s) : AbstractIo(s) {}

    void load();
    void save();
  private:
    QDomDocument document;

};


#endif // XMLIO_HPP
