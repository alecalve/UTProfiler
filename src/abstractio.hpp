#ifndef ABSTRACTIO_HPP
#define ABSTRACTIO_HPP 1

#include <vector>
#include <QString>

#include "uv.hpp"

//! Classe abstraite gérant les exports et imports
class AbstractIo {

  public:
    AbstractIo(const QString &s): identifier(s) {}

    void setIdentifier(const QString &s) { identifier = s; }
    const QString& getIdentifier() { return identifier; }

    virtual std::vector<Uv> load()=0;
    virtual void save(std::vector<Uv>)=0;
    virtual ~AbstractIo() {}

  protected:
    QString identifier;

};

#endif // ABSTRACTIO_HPP
