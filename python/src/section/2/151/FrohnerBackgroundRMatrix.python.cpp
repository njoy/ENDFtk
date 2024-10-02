// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapFrohnerBackgroundRMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::RMatrixLimited::FrohnerBackgroundRMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "FrohnerBackgroundRMatrix",
    "MF2 MT151 section - Frohner parametrisation as a channel's background R-matrix"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, double, double, double, double >(),
    python::arg( "index" ), python::arg( "ed" ), python::arg( "eu" ),
    python::arg( "r0" ), python::arg( "s0" ), python::arg( "ga" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    index    the channel index\n"
    "    ed       the down energy parameter\n"
    "    eu       the up energy parameter\n"
    "    r0       the r0 parameter\n"
    "    s0       the s0 parameter\n"
    "    ga       the ga parameter"
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

    "S0",
    &Component::S0,
    "The S0 parameter in the SAMMY parametrisation"
  )
  .def_property_readonly(

    "GA",
    &Component::GA,
    "The GA parameter in the SAMMY parametrisation"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf2
