// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/6.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapGSection_16( python::module&, python::module& );

void wrapFile_16( python::module& module, python::module& viewmodule ) {

  // type aliases

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF16",
    "MF16 - photon energy-angle distributions"
  );

  // wrap sections
  wrapGSection_16( submodule, viewmodule );
}
