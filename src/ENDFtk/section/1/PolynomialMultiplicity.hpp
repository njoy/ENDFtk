#ifndef NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY
#define NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY

// system includes

// other includes
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

class Polynomial : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;

  /* get methods */
  static constexpr int LNU(){ return 1; }
  int NCO() const { return ListRecord::NPL(); } // NC is used for number of lines
  auto coefficients() const { return ListRecord::list(); }
  using ListRecord::NC;
  using ListRecord::print;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
