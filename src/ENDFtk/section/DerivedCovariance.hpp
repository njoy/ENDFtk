#ifndef NJOY_ENDFTK_SECTION_DERIVEDCOVARIANCE
#define NJOY_ENDFTK_SECTION_DERIVEDCOVARIANCE

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/DerivedRedundant.hpp"
#include "ENDFtk/section/DerivedRatioToStandard.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  using DerivedCovariance = std::variant< DerivedRedundant,
                                          DerivedRatioToStandard >;

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
