// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/14.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
namespace mf14 {

  void wrapIsotropic( python::module&, python::module& );
  void wrapIsotropicDiscretePhoton( python::module&, python::module& );
}

void wrapSection_14( python::module& module, python::module& viewmodule ) {

  // type aliases

  // wrap components
  mf14::wrapIsotropic( module, viewmodule );
  mf14::wrapIsotropicDiscretePhoton( module, viewmodule );

  // wrap views created by this section

  // create the section
}
