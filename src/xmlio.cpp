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

        uv.setAttribute(QString::fromStdString("code"), it->getCode());
        uv.setAttribute(QString::fromStdString("descr"), it->getDescription());
        if (it->getOuvertureAutomne()) {
            QDomElement semestre = doc.createElement("semestre");
            semestre.setAttribute(QString::fromStdString("nom"), "A");
            uv.appendChild(semestre);
        }

        if (it->getOuverturePrintemps()) {
            QDomElement semestre = doc.createElement("semestre");
            semestre.setAttribute(QString::fromStdString("nom"), "P");
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
        QString code, descr;

        QDomNode node = uvs.at(i);
        QDomElement element = node.toElement();

        code = element.attribute("code");
        descr = element.attribute("descr");
        Uv uv = Uv(code, descr);

        //QDomNodeList rec = children(node, "recompenses");


        QDomElement semestre = node.firstChildElement("semestre");

        for(; !semestre.isNull(); semestre=semestre.nextSiblingElement("semestre")) {
            QString nom = semestre.attribute("nom");

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
