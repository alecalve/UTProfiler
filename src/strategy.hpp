#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "dossier.hpp"
#include "solvingcontext.hpp"

//! Classe abstraite des stratégies de résolution des complétions de dossier
class Strategy {
  public:

    //! À partir d’un dossier et du contexte de complétion, renvoie le dossier complété
    virtual Dossier autocomplete(Dossier, SolvingContext)=0;
};

//! Classe de stratégie de complétion concrète
class ConcreteStrategy : public Strategy {
  public:

    //! Algorithme de complétion d’un dossier
    Dossier autocomplete(Dossier, SolvingContext) { return Dossier("toto"); }
};

//! Classe gérant la complétion des dossiers
class Completion {

  public:

    //! Fait appel à la stratégie mise en place pour résoudre la complétion du dossier
    Dossier solve(Dossier d, SolvingContext s) { return strategy->autocomplete(d, s); }

    //! Met en place une stratégie pour résoudre la complétion d’un dossier
    void setStrategy(Strategy *s) { strategy = s; }

  private:

    //! Stratégie de complétion d’un dossier
    Strategy *strategy;
};

#endif //STRATEGY_HPP
