template<>
class Type< 13 > : protected Base {
public:

#include "ENDFtk/section/13/Subsection.hpp"

  std::optional< TabulationRecord > table;
  std::vector< Subsection > subsections;

#include "ENDFtk/section/13/src/readTable.hpp"
#include "ENDFtk/section/13/src/readSubsections.hpp"
#include "ENDFtk/section/13/src/ctor.hpp"
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;

#include "ENDFtk/section/13/src/energies.hpp"
#include "ENDFtk/section/13/src/crossSections.hpp"
};
