template<>
class Type< 2 > : protected Base {
public:
#include "ENDFtk/section/2/src/ctor.hpp"

  CONT isotope;
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
};
