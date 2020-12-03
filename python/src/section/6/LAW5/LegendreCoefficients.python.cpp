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
namespace law5 {

void wrapLegendreCoefficients( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LegendreCoefficients",
    "MF6 section - LAW=5 - charged particle elastic scattering given as\n"
    "                      Legendre coeffcients"
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

    "LTP",
    [] ( const Component& self ) { return self.LTP(); },
    "The representation type"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
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
    "The Legendre order or number of cosine values"
  )
  .def_property_readonly(

    "legendre_order",
    &Component::legendreOrder,
    "The Legendre order or number of cosine values"
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

} // namespace law5
} // namespace mf6
