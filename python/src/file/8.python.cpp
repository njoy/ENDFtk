// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/8.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_8_457( python::module& );

void wrapFile_8( python::module& module ) {

  // type aliases

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF8",
    "MF8 - radioactive decay and fission product yield data"
  );

  // wrap sections
  wrapSection_8_457( submodule );

  //! @todo finish wrapping MF2
}
