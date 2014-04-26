#include "uv.hpp"

unsigned int Uv::getCredits() const {
  unsigned int ret = 0;
  for(auto it=recompenses.begin(); it!= recompenses.end(); it++) {
    ret += it->second;
  }
  return ret;
}
