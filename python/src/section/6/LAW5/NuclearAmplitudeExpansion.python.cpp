// system includes
#include <complex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law5 {

void wrapNuclearAmplitudeExpansion( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "NuclearAmplitudeExpansion",
    "MF6 section - LAW=5 - charged particle elastic scattering given\n"
    "                      as nuclear amplitude expansion"
  );

  // wrap the section
  component
  .def(

    python::init< double, int, std::vector< double >&&,
                  std::vector< std::complex< double > >&& >(),
    python::arg( "energy" ), python::arg( "nl" ),
    python::arg( "b" ), python::arg( "a" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    energy    the incident energy value\n"
    "    nl        the Legendre order\n"
    "    b         the scattering coefficients (for expanding the nuclear\n"
    "              scattering cross section)\n"
    "    a         the interference coefficients (for expanding the\n"
    "              nuclear scattering amplitude matrix)"
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

    "B",
    [] ( const Component& self ) -> DoubleRange
       { return self.B(); },
    "The scattering coefficients"
  )
  .def_property_readonly(

    "scattering_coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.scatteringCoefficients(); },
    "The scattering coefficients"
  )
  .def_property_readonly(

    "AI",
    [] ( const Component& self ) -> DoubleRange
       { return self.AI(); },
    "The interference coefficients"
  )
  .def_property_readonly(

    "imaginary_interference_coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.imaginaryInterferenceCoefficients(); },
    "The interference coefficients"
  )
  .def_property_readonly(

    "AR",
    [] ( const Component& self ) -> DoubleRange
       { return self.AR(); },
    "The interference coefficients"
  )
  .def_property_readonly(

    "real_interference_coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.realInterferenceCoefficients(); },
    "The interference coefficients"
  )
  .def_property_readonly(

    "A",
    [] ( const Component& self ) -> ComplexRange
       { return self.A(); },
    "The interference coefficients"
  )
  .def_property_readonly(

    "interference_coefficients",
    [] ( const Component& self ) -> ComplexRange
       { return self.interferenceCoefficients(); },
    "The interference coefficients"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law5
} // namespace mf6
