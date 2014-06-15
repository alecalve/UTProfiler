#include "xmlio.hpp"

#include <QTextStream>

#include "exceptions.hpp"
#include "uv.hpp"
#include "dossier.hpp"

#define UVM UvManager::getInstance()
#define CUM CategorieUVManager::getInstance()
#define NUM NoteUVManager::getInstance()
#define FM FormationManager::getInstance()
#define DM DossierManager::getInstance()

void XmlIo::save() {

    std::vector<Uv> uvs = UVM->iterator();
    std::vector<CategorieUV> cats = CUM->iterator();
    std::vector<NoteUV> notes = NUM->iterator();
    std::vector<Formation> formations = FM->iterator();
    std::vector<Dossier> dossiers = DM->iterator();

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
            uv.setAttribute(QString::fromStdString("automne"), "1");
        }

        if (it->getOuverturePrintemps()) {
            uv.setAttribute(QString::fromStdString("printemps"), "1");
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

        cat.setAttribute(QString::fromStdString("name"), it->getName());
        cat.setAttribute(QString::fromStdString("longname"), it->getLongName());

        rootCategories.appendChild(cat);
    }

    QDomElement rootNotes = doc.createElement("notes");
    root.appendChild(rootNotes);

    for(auto it=notes.begin(); it!=notes.end(); it++) {
        QDomElement note = doc.createElement("note");

        note.setAttribute(QString::fromStdString("name"), it->getName());
        note.setAttribute(QString::fromStdString("reussite"), it->getReussite());

        rootNotes.appendChild(note);
    }

    QDomElement rootFormations = doc.createElement("formations");
    root.appendChild(rootFormations);

    for(auto it=formations.begin(); it!=formations.end(); it++) {
        QDomElement formation = doc.createElement("formation");

        formation.setAttribute(QString::fromStdString("abbr"), it->getName());
        formation.setAttribute(QString::fromStdString("name"), it->getLongName());
        if (it->hasParent()) {
            formation.setAttribute(QString::fromStdString("parent"), it->getParent().getName());
        }

        std::map<CategorieUV, int> requirementsV = it->getRequirements();
        for(auto i=requirementsV.begin(); i!=requirementsV.end(); i++) {
            QDomElement requirement = doc.createElement("requirement");
            requirement.setAttribute(QString::fromStdString("categorie"), i->first.getName());
            requirement.setAttribute(QString::fromStdString("credits"), i->second);
            formation.appendChild(requirement);
        }

        std::vector<Uv> uvs = it->getUvs();
        for(auto i=uvs.begin(); i!=uvs.end(); i++) {
            QDomElement uv = doc.createElement("uvformation");
            uv.setAttribute(QString::fromStdString("name"), i->getName());
            formation.appendChild(uv);
        }

        rootFormations.appendChild(formation);
    }

    QDomElement rootDossiers= doc.createElement("dossiers");
    root.appendChild(rootDossiers);

    for(auto it=dossiers.begin(); it!=dossiers.end(); it++) {
        QDomElement dossier = doc.createElement("dossier");

        dossier.setAttribute(QString::fromStdString("login"), it->getName());
        dossier.setAttribute(QString::fromStdString("extrascolaire"), QString::number(it->getExtraScolaire()));

        std::vector<Formation> formations = it->getFormations();
        for(auto i=formations.begin(); i!=formations.end(); i++) {
            QDomElement formation = doc.createElement("formationetu");
            formation.setAttribute(QString::fromStdString("name"), i->getName());
            dossier.appendChild(formation);
        }

        std::vector<Semestre> semestres = it->getSemestres();
        for(auto i=semestres.begin(); i!=semestres.end(); i++) {
            QDomElement semestre = doc.createElement("semestreetu");
            semestre.setAttribute(QString::fromStdString("nom"), i->getName());
            semestre.setAttribute(QString::fromStdString("formation"), i->getFormation().getName());
            semestre.setAttribute(QString::fromStdString("semestre"), i->getSemestre().representation);

            std::map<QString, QString> resultats = i->getResultats();
            for(auto res=resultats.begin(); res!=resultats.end(); res++) {
                QDomElement resultat = doc.createElement("resultat");
                resultat.setAttribute(QString::fromStdString("uv"), res->first);
                resultat.setAttribute(QString::fromStdString("note"), res->second);
                semestre.appendChild(resultat);
            }

            dossier.appendChild(semestre);
        }

        std::vector<Equivalence> equivalences = it->getEquivalences();
        for(auto i=equivalences.begin(); i!=equivalences.end(); i++) {
            QDomElement equivalence = doc.createElement("equivalence");
            equivalence.setAttribute(QString::fromStdString("nom"), i->getName());
            equivalence.setAttribute(QString::fromStdString("explication"), i->getExplication());
            equivalence.setAttribute(QString::fromStdString("semestre"), i->getSemestre().representation);

            std::map<CategorieUV, unsigned int> credits = i->getCredits();
            for(auto res=credits.begin(); res!=credits.end(); res++) {
                QDomElement resultat = doc.createElement("credit");
                resultat.setAttribute(QString::fromStdString("categorie"), res->first.getName());
                resultat.setAttribute(QString::fromStdString("credits"), res->second);
                equivalence.appendChild(resultat);
            }

            dossier.appendChild(equivalence);
        }

        rootDossiers.appendChild(dossier);
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
        int pr, aut;

        QDomNode node = uvs.at(i);
        QDomElement element = node.toElement();

        code = element.attribute("code");
        descr = element.attribute("descr");
        pr = element.attribute("printemps").toInt();
        aut = element.attribute("automne").toInt();

        Uv uv = Uv(code, descr);

        if (pr) { uv.setOuverturePrintemps(true); }
        if (aut) { uv.setOuvertureAutomne(true); }

        QDomElement recompense = node.firstChildElement("recompense");

        for(; !recompense.isNull(); recompense=recompense.nextSiblingElement("recompense")) {
            QString cat = recompense.attribute("cat");
            unsigned int creds = recompense.attribute("ects").toUInt();
            uv.setCredits(cat, creds);
        }


        UVM->addItem(uv);
    }

    QDomNodeList cats = document.elementsByTagName("categorie");

    for(int i=0; i<cats.count(); i++) {
        QString nom, longname;

        QDomNode node = cats.at(i);
        QDomElement element = node.toElement();

        nom = element.attribute("name");
        longname = element.attribute("longname");
        CategorieUV cat(nom, longname);

        CUM->addItem(cat);
    }

    QDomNodeList notes = document.elementsByTagName("note");

    for(int i=0; i<notes.count(); i++) {
        QString nom;
        bool reussite;

        QDomNode node = notes.at(i);
        QDomElement element = node.toElement();

        nom = element.attribute("name");
        reussite = element.attribute("reussite").toInt();
        NoteUV note(nom, reussite);
        NUM->addItem(note);
    }

    QDomNodeList formations = document.elementsByTagName("formation");

    for(int i=0; i<formations.count(); i++) {
        QDomNode node = formations.at(i);
        QDomElement element = node.toElement();

        QString nom, abbr, parent;
        nom = element.attribute("name");
        abbr = element.attribute("abbr");
        parent = element.attribute("parent");

        Formation f(abbr,nom);

        if (!parent.isEmpty()) {
            f.setParent(parent);
        }

        QDomElement requirement = node.firstChildElement("requirement");

        for(; !requirement.isNull(); requirement=requirement.nextSiblingElement("requirement")) {
            QString cat = requirement.attribute("categorie");
            unsigned int credits = requirement.attribute("credits").toUInt();
            f.setRequirements(cat, credits);
        }

        QDomElement uv = node.firstChildElement("uvformation");

        for(; !uv.isNull(); uv=uv.nextSiblingElement("uvformation")) {
            QString name= uv.attribute("name");
            Uv u = UVM->getItem(name);
            f.addUv(u);
        }

        FM->addItem(f);
    }

    QDomNodeList dossiers = document.elementsByTagName("dossier");

    for(int i=0; i<dossiers.count(); i++) {
        QDomNode node = dossiers.at(i);
        QDomElement element = node.toElement();

        QString nom;
        bool extrascolaire;
        nom = element.attribute("login");
        std::cout<<nom.toStdString()<<std::endl;
        extrascolaire = (bool) element.attribute("extrascolaire").toInt();

        Dossier d(nom);
        d.setExtraScolaire(extrascolaire);

        QDomElement formation = node.firstChildElement("formationetu");

        for(; !formation.isNull(); formation=formation.nextSiblingElement("formationetu")) {
            QString name = formation.attribute("name");
            d.addFormation(FM->getItem(name));
        }

        QDomElement semestre = node.firstChildElement("semestreetu");

        for(; !semestre.isNull(); semestre=semestre.nextSiblingElement("semestreetu")) {
            QString name= semestre.attribute("nom");
            QString formation = semestre.attribute("formation");
            QString sem = semestre.attribute("semestre");

            Semestre s(name);
            s.setFormation(FM->getItem(formation));
            s.setSemestre(SemestreT(sem));

            QDomElement resultat = semestre.firstChildElement("resultat");

            for(; !resultat.isNull(); resultat=resultat.nextSiblingElement("resultat")) {
                QString uv= resultat.attribute("uv");
                QString note = resultat.attribute("note");
                s.setResultat(uv, note);
            }
            d.addSemestre(s);
        }

        QDomElement equivalence = node.firstChildElement("equivalence");

        for(; !equivalence.isNull(); equivalence=equivalence.nextSiblingElement("equivalence")) {
            QString name= equivalence.attribute("nom");
            QString explication= equivalence.attribute("explication");
            QString sem = equivalence.attribute("semestre");

            Equivalence eq(name, explication);
            eq.setSemestre(sem);

            QDomElement credit = equivalence.firstChildElement("credit");

            for(; !credit.isNull(); credit=credit.nextSiblingElement("credit")) {
                QString credits = credit.attribute("credits");
                QString cat = credit.attribute("categorie");
                eq.setCredits(CUM->getItem(cat), credits.toUInt());
            }
            d.addEquivalence(eq);
        }
        DM->addItem(d);
    }

}
