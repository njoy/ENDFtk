template<>
class Type< 13 > : protected Base {
public:

#include "ENDFtk/section/13/Subsection.hpp"

  TabulationRecord table;

#include "ENDFtk/section/13/src/readTable.hpp"
#include "ENDFtk/section/13/src/ctor.hpp"
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
};
