// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapWattSpectrum( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 5 >::WattSpectrum;
  using Parameter = njoy::ENDFtk::section::Type< 5 >::Parameter;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "WattSpectrum",
    "MF5 section - the Watt fission spectrum (LF=11)"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( Parameter a, Parameter b )
                     { return Component( std::move( a ), std::move( b ) ); } ),
    python::arg( "a" ), python::arg( "b" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    a       the parameter function a\n"
    "    b       the parameter function b"
  )
  .def_property_readonly(

    "LF",
    [] ( const Component& self ) { return self.LF(); },
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "a",
    &Component::a,
    "The a parameter data"
  )
  .def_property_readonly(

    "b",
    &Component::b,
    "The b parameter data"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
