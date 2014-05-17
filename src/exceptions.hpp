#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP 1

#include <QString>

class Exception{
    QString info;
public :
    Exception(const QString& s):info(s){}
    const QString& getinfo() const {return info;}
};

#endif // EXCEPTIONS_HPP
