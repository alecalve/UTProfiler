#ifndef UVMANAGER_H
#define UVMANAGER_H 1

#include "manager.hpp"
#include "uv.hpp"
#include "singleton.hpp"

typedef Singleton<Manager<Uv>> UvManager;

#endif // UVMANAGER_H
