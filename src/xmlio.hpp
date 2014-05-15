#ifndef XMLIO_HPP
#define XMLIO_HPP 1

#include <QtXml>
#include <QFile>
#include <QString>
#include <vector>

#include "abstractio.hpp"

//! Implémentation de AbstractIo pour les exports XML
class XmlIo : public AbstractIo {

  public:
    XmlIo(const QString &s) : AbstractIo(s) {}

    std::vector<Uv> load();
    void saveItem(const Uv&) {}

  protected:
    QDomDocument document;

};


#endif // XMLIO_HPP
