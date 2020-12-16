// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSammyBackgroundRMatrix( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SammyBackgroundRMatrix",
    "MF2 MT151 section - SAMMY parametrisation as a channel's background R-matrix"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, double,
                  double, double, double, double, double >(),
    python::arg( "index" ), python::arg( "ed" ), python::arg( "eu" ),
    python::arg( "r0" ), python::arg( "r1" ), python::arg( "r2" ),
    python::arg( "s0" ), python::arg( "s1" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    index    the channel index\n"
    "    ed       the down energy parameter\n"
    "    eu       the up energy parameter\n"
    "    r0       the r0 parameter\n"
    "    r1       the r1 parameter\n"
    "    r2       the r2 parameter\n"
    "    s0       the s0 parameter\n"
    "    s1       the s1 parameter"
  )
  .def_property_readonly(

    "LBK",
    [] ( const Component& self ) { return self.LBK(); },
    "The background R-matrix representation"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The background R-matrix representation"
  )
  .def_property_readonly(

    "LCH",
    [] ( const Component& self ) { return self.LCH(); },
    "The channel index"
  )
  .def_property_readonly(

    "channel_index",
    [] ( const Component& self ) { return self.channelIndex(); },
    "The channel index"
  )
  .def_property_readonly(

    "ED",
    &Component::ED,
    "The energy down parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "EU",
    &Component::EU,
    "The energy up parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "R0",
    &Component::R0,
    "The R0 parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "R1",
    &Component::R1,
    "The R1 parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "R2",
    &Component::R2,
    "The R2 parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "S0",
    &Component::S0,
    "The S0 parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "S1",
    &Component::S1,
    "The S1 parameter in the SAMMY parametrisation"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
