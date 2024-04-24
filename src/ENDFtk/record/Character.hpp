#ifndef NJOY_ENDFTK_RECORD_CHARACTER
#define NJOY_ENDFTK_RECORD_CHARACTER

// system includes

// other includes
#include "tools/disco/Character.hpp"
#include "ENDFtk/record/helper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template< int w >
  struct Character {
    static constexpr std::size_t width = w;
    using Type = std::string;
    using Parser = njoy::tools::disco::Character< width >;

    static constexpr const Type& defaultValue = helper::defaultString< w >;
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
