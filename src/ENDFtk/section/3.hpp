template<>
class Type< 3 > : protected Base {
public:

  /* fields */
  TabulationRecord table;

  /* methods */
#include "ENDFtk/section/3/src/ctor.hpp"

#include "ENDFtk/section/3/src/print.hpp"
    
  using Base::MT;
  using Base::sectionNumber;
  using Base::ZA;
  using Base::atomicWeightRatio;
};

