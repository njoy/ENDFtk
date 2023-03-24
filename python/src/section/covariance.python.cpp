// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/covariance.hpp"
#include "definitions.hpp"
#include "views.hpp"

// declarations - covariance components
void wrapCovariancePairs( python::module&, python::module& );
void wrapRectangularMatrix( python::module&, python::module& );
void wrapSquareMatrix( python::module&, python::module& );
void wrapCovariancePairs( python::module&, python::module& );
void wrapRectangularMatrix( python::module&, python::module& );
void wrapReactionBlock( python::module&, python::module& );

// namespace aliases
namespace python = pybind11;

void wrapCovariance( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::ExplicitCovariance;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Component >(
      viewmodule,
      "any_view< variant< CovariancePairs, SquareMatrix, "
                         "RectangularMatrix >, random_access >" );

  // wrap covariance components
  wrapCovariancePairs( module, viewmodule );
  wrapRectangularMatrix( module, viewmodule );
  wrapSquareMatrix( module, viewmodule );
}
