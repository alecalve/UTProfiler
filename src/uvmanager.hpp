#ifndef UVMANAGER_H
#define UVMANAGER_H 1

#include "uv.hpp"

class UvManager {

  public:
    static UvManager* getInstance();

  private:
    UvManager();
    UvManager(const UvManager&);
    UvManager operator=(const UvManager&);
    static UvManager *instance;
};

#endif // UVMANAGER_H
