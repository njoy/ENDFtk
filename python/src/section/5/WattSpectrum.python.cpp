// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapWattSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 5 >;
  using Component = Section::WattSpectrum;
  using Parameter = Section::Parameter;

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

    //! @todo pybind11 lambda move custom type workaround
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

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
