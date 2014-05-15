#include "uv.hpp"


//! Getter des crédits, additionne les valeurs des récompenses
unsigned int Uv::getCredits() const {
  unsigned int ret = 0;
  for(auto it=recompenses.begin(); it!= recompenses.end(); it++) {
    ret += it->second;
  }
  return ret;
}
