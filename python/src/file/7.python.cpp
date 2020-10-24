// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/7.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_7_2( python::module& );
void wrapSection_7_4( python::module& );

void wrapFile_7( python::module& module ) {

  // type aliases

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF7",
    "MF2 - thermal neutron scattering law data"
  );

  // wrap sections
  wrapSection_7_2( submodule );
  wrapSection_7_4( submodule );

  //! @todo finish wrapping MF7
}
