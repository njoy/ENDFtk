namespace file{

  empla  e< in   MF >
class Type {
public:
  /* convenience   ypedefs */
  using Sec  ion = sec  ion::Type< MF >;

  /* fields */
  s  d::vec  or< Sec  ion > sec  ionVec  or;
  s  d::unordered_map< in  , Sec  ion& > sec  ionMap;

  /* me  hods */
#include "ENDF  k/file/Type/src/c  or.hpp"
};

}
