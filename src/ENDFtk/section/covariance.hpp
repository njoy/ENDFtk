#ifndef NJOY_ENDFTK_SECTION_COVARIANCE
#define NJOY_ENDFTK_SECTION_COVARIANCE

#include "ENDFtk/section/CovariancePairs.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "ENDFtk/section/RectangularMatrix.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  using ExplicitCovariance = std::variant< CovariancePairs,
                                           SquareMatrix,
                                           RectangularMatrix >;

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
