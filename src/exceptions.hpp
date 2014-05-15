#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP 1

#include <exception>

class ItemNotFoundException: public std::exception {
    virtual const char *what() const throw() {
        return "L’objet demandé n’a pas été trouvé";
    }
};

class IOException: public std::exception {
    virtual const char *what() const throw() {
        return "Erreur dans une opération lecture/écriture";
    }
};

class XmlIOException: public IOException {
    virtual const char *what() const throw() {
        return "Erreur dans le parsing du fichier XML";
    }
};

#endif // EXCEPTIONS_HPP
