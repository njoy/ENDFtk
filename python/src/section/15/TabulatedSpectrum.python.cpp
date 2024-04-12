// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/15.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf15 {

void wrapTabulatedSpectrum( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 15 >;
  using Component = Section::TabulatedSpectrum;
  using Distribution = Section::TabulatedSpectrum::OutgoingEnergyDistribution;
  using DistributionRange = RandomAccessAnyView< Distribution >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Distribution >(
      viewmodule,
      "any_view< MF15::OutgoingEnergyDistribution, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedSpectrum",
    "MF15 section - arbitrary tabulated energy distribution (LF=1)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< Distribution >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "distributions" ),
    "Initialise the scattering radius\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    distributions    the sequence of outgoing energy distributions"
  )
  .def_property_readonly(

    "LF",
    [] ( const Component& self ) { return self.LF(); },
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "NE",
    [] ( const Component& self ) { return self.NE(); },
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    [] ( const Component& self ) { return self.numberIncidentEnergies(); },
    "The number of incident energy values"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energies"
  )
  .def_property_readonly(

    "outgoing_distributions",
    [] ( const Component& self ) -> DistributionRange
       { return self.outgoingDistributions(); },
    "The outgoing energy distributions (one for each incident energy)"
  );

  // add standard tab2 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf15
