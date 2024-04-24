// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {

void wrapChargedParticleElasticScattering( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ChargedParticleElasticScattering;
  using Distribution = Section::ChargedParticleElasticScattering::Variant;
  using DistributionRange = RandomAccessAnyView< Distribution >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Distribution >(
      viewmodule,
      "any_view< variant< NuclearAmplitudeExpansion, LegendreCoefficients,"
                         "NuclearPlusInterference >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ChargedParticleElasticScattering",
    "MF6 section - LAW=5 - charged particle elastic scattering"
  );

  // wrap the section
  component
  .def(

    python::init< double, int, std::vector< long >&&, std::vector< long >&&,
                  std::vector< Distribution >&& >(),
    python::arg( "spin" ), python::arg( "lidp" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "distributions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    spin             the spin of the charged particle\n"
    "    lidp             the identicle particle flag\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    distributions    the data for each incident energy value"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "SPI",
    &Component::SPI,
    "The spin of the particle"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The spin of the particle"
  )
  .def_property_readonly(

    "LIDP",
    &Component::LIDP,
    "Whether or not the particles are identical"
  )
  .def_property_readonly(

    "identical_particles",
    &Component::identicalParticles,
    "Whether or not the particles are identical"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    &Component::numberIncidentEnergies,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "distributions",
    [] ( const Component& self ) -> DistributionRange
       { return self.distributions(); },
    "The distributions"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf6
