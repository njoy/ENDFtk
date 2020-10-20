#ifndef NJOY_ENDFTK_RECORD_REAL
#define NJOY_ENDFTK_RECORD_REAL

// system includes

// other includes
#include "disco.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  struct Real {
    static constexpr std::size_t width = 11;
    using Type = double;
    using Parser = disco::ENDF;
  
    static constexpr Type defaultValue = 0.0;
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
