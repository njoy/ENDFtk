// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/CovariancePairs.hpp"
#include "ENDFtk/section/RectangularMatrix.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"
#include "ENDFtk/section/DerivedRatioToStandard.hpp"
#include "ENDFtk/section/DerivedRedundant.hpp"
#include "ENDFtk/section/DerivedCovariance.hpp"
#include "ENDFtk/section/ReactionBlock.hpp"
#include "definitions.hpp"
#include "views.hpp"

// declarations - covariance components
void wrapCovariancePairs( python::module&, python::module& );
void wrapRectangularMatrix( python::module&, python::module& );
void wrapSquareMatrix( python::module&, python::module& );
void wrapDerivedRatioToStandard( python::module&, python::module& );
void wrapDerivedRedundant( python::module&, python::module& );
void wrapReactionBlock( python::module&, python::module& );

// namespace aliases
namespace python = pybind11;

void wrapCovariance( python::module& module, python::module& viewmodule ) {

  // wrap covariance components
  wrapCovariancePairs( module, viewmodule );
  wrapRectangularMatrix( module, viewmodule );
  wrapSquareMatrix( module, viewmodule );

  // type aliases
  using ExplicitCovariance = njoy::ENDFtk::section::ExplicitCovariance;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ExplicitCovariance >(
      viewmodule,
      "any_view< variant< CovariancePairs, SquareMatrix, "
                         "RectangularMatrix >, random_access >" );

  // wrap covariance components
  wrapDerivedRatioToStandard( module, viewmodule );
  wrapDerivedRedundant( module, viewmodule );

  // type aliases
  using DerivedCovariance = njoy::ENDFtk::section::DerivedCovariance;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DerivedCovariance >(
      viewmodule,
      "any_view< variant< DerivedRatioToStandard, DerivedRedundant >, random_access >" );

  // wrap covariance components
  wrapReactionBlock( module, viewmodule );
}
