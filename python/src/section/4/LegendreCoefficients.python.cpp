// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreCoefficients( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using Component = Section::LegendreCoefficients;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LegendreCoefficients",
    "MF4 section - an angular distribution given as Legendre coefficients"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "coefficients" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    energy          the incident energy\n"
    "    coefficients    the Legendre coefficients"
  )
  .def_property_readonly(

    "E",
    &Component::E,
    "The incident energy for which the angular distribution is given"
  )
  .def_property_readonly(

    "incident_energy",
    &Component::incidentEnergy,
    "The incident energy for which the angular distribution is given"
  )
  .def_property_readonly(

    "NL",
    &Component::NL,
    "The Legendre order for the angular distribution"
  )
  .def_property_readonly(

    "legendre_order",
    &Component::legendreOrder,
    "The Legendre order for the angular distribution"
  )
  .def_property_readonly(

    "A",
    [] ( const Component& self ) -> DoubleRange
       { return self.A(); },
    "The Legendre coefficients in the distribution (a0 is not present and\n"
    "assumed to be equal to 1)"
  )
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.coefficients(); },
    "The Legendre coefficients in the distribution (a0 is not present and\n"
    "assumed to be equal to 1)"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
