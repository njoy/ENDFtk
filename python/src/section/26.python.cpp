// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/26.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf26 {

  // declarations - components
  void wrapMultiplicity( python::module&, python::module& );

  void wrapEnergyTransfer( python::module&, python::module& );         // law=8
}

void wrapSection_26( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;

  // wrap components

  // LAW = 8 - - - - - - - - - - - - - - - - - - - - - -

  mf26::wrapEnergyTransfer( module, viewmodule );

  mf26::wrapMultiplicity( module, viewmodule );

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF26 section - secondary distributions for photo- and electro-atomic interactions"
  );

  // wrap the section

  // add standard section definitions
//  addStandardSectionDefinitions< Section >( section );
}
