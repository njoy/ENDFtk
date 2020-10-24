#ifndef NJOY_ENDFTK_SECTION_1_TABULATEDMULTIPLICITY
#define NJOY_ENDFTK_SECTION_1_TABULATEDMULTIPLICITY

// system includes

// other includes
#include "ENDFtk/TabulationRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

class Tabulated : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  static constexpr int LNU(){ return 2; }
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  auto energy() const { return TabulationRecord::x(); }
  auto nubar() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
