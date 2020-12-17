// system includes
#include <complex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law2 {

void wrapLegendreCoefficients( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LegendreCoefficients",
    "MF6 section - LAW=2 - an angular distribution given as a Legendre coefficients"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "coefficients" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    energy          the incident energy value\n"
    "    coefficients    the Legendre coefficients"
  )
  .def_property_readonly(

    "E",
    &Component::E,
    "The incident energy value"
  )
  .def_property_readonly(

    "incident_energy",
    &Component::incidentEnergy,
    "The incident energy value"
  )
  .def_property_readonly(

    "LANG",
    [] ( const Component& self ) { return self.LANG(); },
    "The representation type"
  )
  .def_property_readonly(

    "NW",
    &Component::NW,
    "The number of values in this component"
  )
  .def_property_readonly(

    "NL",
    &Component::NL,
    "The Legendre order"
  )
  .def_property_readonly(

    "legendre_order",
    &Component::legendreOrder,
    "The Legendre order"
  )
  .def_property_readonly(

    "A",
    [] ( const Component& self ) -> DoubleRange
       { return self.A(); },
    "The Legendre coefficients"
  )
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.coefficients(); },
    "The Legendre coefficients"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law2
} // namespace mf6
