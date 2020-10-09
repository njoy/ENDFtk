// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/2.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_2_151( python::module& );
void wrapSection_2_152( python::module& );

void wrapFile_2( python::module& module ) {

  // type aliases

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF2",
    "MF2 - resonance parameters"
  );

  // wrap sections
  wrapSection_2_151( submodule );
  wrapSection_2_152( submodule );

  //! @todo finish wrapping MF2
}
