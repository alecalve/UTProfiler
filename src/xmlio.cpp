#include "xmlio.hpp"

#include <QTextStream>
#include <iostream>

#include "exceptions.hpp"
#include "uv.hpp"

#define UVM UvManager::getInstance()
#define CUM CategorieUVManager::getInstance()
#define NUM NoteUVManager::getInstance()

void XmlIo::save() {

    std::vector<Uv> uvs = UVM->iterator();
    std::vector<CategorieUV> cats = CUM->iterator();
    std::vector<NoteUV> notes = NUM->iterator();

    QDomDocument doc;
    QDomElement root = doc.createElement("sauvegarde");
    doc.appendChild(root);
    QDomElement rootUvs = doc.createElement("uvs");
    root.appendChild(rootUvs);

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

        auto recompenses = it->getRecompenses();
        for(const auto &rec : recompenses) {
            QDomElement recompense = doc.createElement("recompense");
            recompense.setAttribute("cat", rec.first);
            recompense.setAttribute("ects", rec.second);
            uv.appendChild(recompense);
        }

        rootUvs.appendChild(uv);
    }

    QDomElement rootCategories = doc.createElement("categories");
    root.appendChild(rootCategories);

    for(auto it=cats.begin(); it!=cats.end(); it++) {
        QDomElement cat = doc.createElement("categorie");

        cat.setAttribute(QString::fromStdString("nom"), it->nom);
        cat.setAttribute(QString::fromStdString("abbr"), it->abbreviation);

        rootCategories.appendChild(cat);
    }

    QDomElement rootNotes = doc.createElement("notes");
    root.appendChild(rootNotes);

    for(auto it=notes.begin(); it!=notes.end(); it++) {
        QDomElement note = doc.createElement("note");

        note.setAttribute(QString::fromStdString("nom"), it->nom);
        note.setAttribute(QString::fromStdString("reussite"), it->reussite);

        rootNotes.appendChild(note);
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

void XmlIo::load() {

    document = QDomDocument();
    QFile fichier(identifier);

    if (!fichier.open(QIODevice::ReadOnly)) {
        throw Exception("impossible d'ouvrir le fichier");
    }

    int line = 0;
    QString error = "";
    if (!document.setContent(&fichier, &error, &line)) {
        fichier.close();
        QString strline = QString::number(line);
        error.prepend("Fichier invalide : '");
        error.append("', ligne ");
        error.append(strline);
        throw Exception(error);
    }

    fichier.close();

    QDomNodeList uvs = document.elementsByTagName("uv");

    for(int i=0; i<uvs.count(); i++) {
        QString code, descr;

        QDomNode node = uvs.at(i);
        QDomElement element = node.toElement();

        code = element.attribute("code");
        descr = element.attribute("descr");
        Uv uv = Uv(code, descr);

        QDomElement recompense = node.firstChildElement("recompense");

        for(; !recompense.isNull(); recompense=recompense.nextSiblingElement("recompense")) {
            QString cat = recompense.attribute("cat");
            unsigned int creds = recompense.attribute("ects").toUInt();
            uv.setCredits(cat, creds);
        }

        QDomElement semestre = node.firstChildElement("semestre");

        for(; !semestre.isNull(); semestre=semestre.nextSiblingElement("semestre")) {
            QString nom = semestre.attribute("nom");

            if (nom == "A") {
                uv.setOuvertureAutomne(true);
            } else if (nom == "P") {
                uv.setOuverturePrintemps(true);
            }
        }

        UVM->addItem(uv);
    }

    QDomNodeList cats = document.elementsByTagName("categorie");

    for(int i=0; i<cats.count(); i++) {
        QString nom, abbr;

        QDomNode node = cats.at(i);
        QDomElement element = node.toElement();

        nom = element.attribute("nom");
        abbr = element.attribute("abbr");
        CategorieUV cat;
        cat.nom = nom;
        cat.abbreviation = abbr;

        CUM->addItem(cat);
    }

    QDomNodeList notes = document.elementsByTagName("note");

    for(int i=0; i<notes.count(); i++) {
        QString nom;
        bool reussite;

        QDomNode node = notes.at(i);
        QDomElement element = node.toElement();

        nom = element.attribute("nom");
        reussite = element.attribute("reussite").toInt();
        NoteUV note;
        note.nom = nom;
        note.reussite= reussite;

        NUM->addItem(note);
    }

}
