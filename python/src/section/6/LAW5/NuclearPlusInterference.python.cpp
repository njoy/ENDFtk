// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law5 {

void wrapNuclearPlusInterference( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ChargedParticleElasticScattering::NuclearPlusInterference;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "NuclearPlusInterference",
    "MF6 section - LAW=5 - charged particle elastic scattering given as\n"
    "                      nuclear plus interference distribution"
  );

  // wrap the section
  component
  .def(

    python::init< double, int,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "ltp" ),
    python::arg( "cosines" ), python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the incident energy value\n"
    "    ltp              the representation type\n"
    "    cosines          the cosine values\n"
    "    probabilities    the probability values"
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
    &Component::LTP,
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

    "MU",
    [] ( const Component& self ) -> DoubleRange
       { return self.MU(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Component& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosine values"
  )
  .def_property_readonly(

    "PNI",
    [] ( const Component& self ) -> DoubleRange
       { return self.PNI(); },
    "The probability values"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.probabilities(); },
    "The probability values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law5
} // namespace mf6
