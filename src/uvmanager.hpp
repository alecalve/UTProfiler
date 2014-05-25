#ifndef UVMANAGER_H
#define UVMANAGER_H 1

#include "manager.hpp"
#include "uv.hpp"
#include "singleton.hpp"

//! Un UvManager est un alias pour un Singleton de Manager d’UV
typedef Singleton<Manager<Uv>> UvManager;

#endif // UVMANAGER_H
