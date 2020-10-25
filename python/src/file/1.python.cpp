// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/1.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrap_1_TabulatedMultiplicity( python::module& );
void wrap_1_PolynomialMultiplicity( python::module& );
void wrapSection_1_451( python::module& );

void wrapFile_1( python::module& module ) {

  // type aliases

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF1",
    "MF1 - general information"
  );

  // wrap sections
  wrap_1_TabulatedMultiplicity( submodule );
  wrap_1_PolynomialMultiplicity( submodule );
  wrapSection_1_451( submodule );

  //! @todo finish wrapping MF1
}
