// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSpecialCase( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::SpecialCase;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SpecialCase",
    "MF2 MT151 section - special case: no parameters are given (LRU=0, LRF=0)"
  );

  // wrap the section
  component
  .def(

    python::init< double, double >(),
    python::arg( "spin" ), python::arg( "ap" ),
    "Initialise the Isotope\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    spin    the target spin\n"
    "    ap      the scattering radius"
  )
  .def_property_readonly(

    "LRU",
    [] ( const Component& self ) { return self.LRU(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) { return self.type(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "LRF",
    [] ( const Component& self ) { return self.LRF(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "LFW",
    [] ( const Component& self ) { return self.LFW(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "average_fission_width_flag",
    [] ( const Component& self ) { return self.averageFissionWidthFlag(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "SPI",
    &Component::SPI,
    "The target spin"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The scattering radius"
  )
  .def_property_readonly(

    "AP",
    &Component::AP,
    "The target spin"
  )
  .def_property_readonly(

    "scattering_radius",
    &Component::scatteringRadius,
    "The target spin"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
