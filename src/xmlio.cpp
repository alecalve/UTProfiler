#include "xmlio.hpp"

#include <QTextStream>
#include <iostream>

#include "exceptions.hpp"
#include "uv.hpp"


void XmlIo::save(std::vector<Uv> uvs) {

    QDomDocument doc;
    QDomElement root = doc.createElement("uvs");
    doc.appendChild(root);

    for(auto it=uvs.begin(); it!=uvs.end(); it++) {
        QDomElement uv = doc.createElement("uv");

        uv.setAttribute(QString::fromStdString("code"), QString::fromStdString(it->getCode()));
        uv.setAttribute(QString::fromStdString("descr"), QString::fromStdString(it->getDescription()));
        if (it->getOuvertureAutomne()) {
            QDomElement semestre = doc.createElement("semestre");
            semestre.setAttribute(QString::fromStdString("nom"), QString::fromStdString("A"));
            uv.appendChild(semestre);
        }

        if (it->getOuverturePrintemps()) {
            QDomElement semestre = doc.createElement("semestre");
            semestre.setAttribute(QString::fromStdString("nom"), QString::fromStdString("P"));
            uv.appendChild(semestre);
        }

        root.appendChild(uv);
    }

    QFile fichier(identifier);

    if (!fichier.open(QIODevice::WriteOnly)) {
        throw Exception("impossible de sauvegarder le fichier");
    }

    //À partir d’ici, tout échec fait perdre les données
    // TODO: sauvegarder le fichier avant de tenter d’écrire

    QString toWrite = doc.toString();
    QTextStream stream(&fichier);
    stream << toWrite;
    fichier.close();

}

std::vector<Uv> XmlIo::load() {

    document = QDomDocument();
    QFile fichier(identifier);

    if (!fichier.open(QIODevice::ReadOnly)) {
        throw Exception("impossible d'ouvrir le fichier");
    }

    if (!document.setContent(&fichier)) {
        fichier.close();
        throw Exception("Le fichier n'est pas valide");
    }

    fichier.close();

    std::vector<Uv> tab;
    QDomNodeList uvs = document.elementsByTagName("uv");

    for(int i=0; i<uvs.count(); i++) {
        std::string code, descr;

        QDomNode node = uvs.at(i);
        QDomElement element = node.toElement();

        code = element.attribute("code").toStdString();
        descr = element.attribute("descr").toStdString();
        Uv uv = Uv(code, descr);

        //QDomNodeList rec = children(node, "recompenses");


        QDomElement semestre = node.firstChildElement("semestre");

        for(; !semestre.isNull(); semestre=semestre.nextSiblingElement("semestre")) {
            std::string nom = semestre.attribute("nom").toStdString();

            if (nom == "A") {
                uv.setOuvertureAutomne(true);
            } else if (nom == "P") {
                uv.setOuverturePrintemps(true);
            }
        }

        tab.push_back(uv);
    }

    return tab;
}
