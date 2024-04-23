#ifndef NJOY_ENDFTK_RECORD_INTEGER
#define NJOY_ENDFTK_RECORD_INTEGER

// system includes

// other includes
#include "tools/disco/Integer.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template< int w >
  struct Integer{
    static constexpr std::size_t width = w;
    using Type = long;
    using Parser = njoy::tools::disco::Integer< width >;

    static constexpr Type defaultValue = 0;
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
