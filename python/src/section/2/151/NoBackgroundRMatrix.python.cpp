// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapNoBackgroundRMatrix( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::NoBackgroundRMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "NoBackgroundRMatrix",
    "MF2 MT151 section - no background is given for the channel"
  );

  // wrap the section
  component
  .def(

    python::init< int >(),
    python::arg( "index" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    index    the channel index"
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
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
