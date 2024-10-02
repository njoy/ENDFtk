// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/15.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf15 {

void wrapOutgoingEnergyDistribution( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 15 >;
  using Component = Section::TabulatedSpectrum::OutgoingEnergyDistribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "OutgoingEnergyDistribution",
    "MF15 section - outgoing energy distribution for a fixed value of E"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "incident" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    incident         the incident energy value\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    energies         the outgoing energy values\n"
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

    "EP",
    [] ( const Component& self ) -> DoubleRange
       { return self.EP(); },
    "The outgoing energy values"
  )
  .def_property_readonly(

    "outgoing_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.outgoingEnergies(); },
    "The outgoing energy values"
  )
  .def_property_readonly(

    "G",
    [] ( const Component& self ) -> DoubleRange
       { return self.G(); },
    "The distribution probabilities"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.probabilities(); },
    "The distribution probabilities"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf15
