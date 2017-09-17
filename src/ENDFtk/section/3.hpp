template<>
class Type< 3 > : protected Base {
public:

  /* fields */
  TabulationRecord table;

  /* methods */
#include "ENDFtk/section/3/src/ctor.hpp"
    
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
};

