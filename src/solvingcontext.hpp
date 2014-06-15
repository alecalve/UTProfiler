#ifndef SOLVINGCONTEXT_HPP
#define SOLVINGCONTEXT_HPP

#include <vector>

#include "uv.hpp"
#include "uvmanager.hpp"

#define UVM UvManager::getInstance()

class SolvingContext {

  public:
    SolvingContext() {}

    inline const std::vector<Uv>& getWishes() const { return wishes; }
    inline const std::vector<Uv>& getRejections() const { return rejections; }

    inline void addWish(Uv u) { wishes.push_back(u); }
    inline void addWish(const QString& u) {
        Uv uv = UVM->getItem(u);
        addWish(uv);
    }

    inline void addRejection(Uv u) { rejections.push_back(u); }
    inline void addRejection(const QString& u) {
        Uv uv = UVM->getItem(u);
        addRejection(uv);
    }

  private:
    std::vector<Uv> wishes;
    std::vector<Uv> rejections;
};

#endif // SOLVINGCONTEXT_HPP
