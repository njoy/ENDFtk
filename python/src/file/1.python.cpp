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
  wrapSection_1_451( submodule );

  //! @todo finish wrapping MF1
}
