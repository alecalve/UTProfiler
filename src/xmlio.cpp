#include "xmlio.hpp"

#include <QTextStream>
#include <iostream>

#include "exceptions.hpp"
#include "uv.hpp"


/*
    QFile fichier(identifier);

    if (!fichier.open(QIODevice::WriteOnly)) {
        throw IOException();
    }

    //À partir d’ici, tout échec fait perdre les données
    // TODO: sauvegarder le fichier avant de tenter d’écrire

    QString toWrite = document.toString();
    QTextStream stream(&fichier);
    stream << toWrite;
    fichier.close();

*/

std::vector<Uv> XmlIo::load() {

    document = QDomDocument();
    QFile fichier(identifier);

    if (!fichier.open(QIODevice::ReadOnly)) {
        throw IOException();
    }

    if (!document.setContent(&fichier)) {
        fichier.close();
        throw XmlIOException();
    }

    fichier.close();

    std::vector<Uv> tab;
    QDomElement dom = document.documentElement();
    QDomNode node = dom.firstChild();
    while (!node.isNull()) {

        QDomElement element = node.toElement();

        std::string code = element.attribute("code").toStdString();
        std::string descr = element.attribute("descr").toStdString();

        Uv u = Uv(code, descr);
        tab.push_back(u);
        node = node.nextSibling();
    }

    return tab;
}
