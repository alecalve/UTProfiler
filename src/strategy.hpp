#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "dossier.hpp"
#include "solvingcontext.hpp"

class Strategy {
  public:
    virtual Dossier autocomplete(Dossier, SolvingContext)=0;
};

class ConcreteStrategy : public Strategy {
  public:
    Dossier autocomplete(Dossier, SolvingContext) { return Dossier("toto"); }
};


class Completion {

  public:
    Dossier solve(Dossier d, SolvingContext s) { return strategy->autocomplete(d, s); }
    void setStrategy(Strategy *s) { strategy = s; }

  private:
    Strategy *strategy;
};

#endif //STRATEGY_HPP
