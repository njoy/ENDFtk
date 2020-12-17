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
namespace law7 {

void wrapAngularDistribution( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::LaboratoryAngleEnergy::AngularDistribution;
  using EnergyDistribution = njoy::ENDFtk::section::Type< 6 >::LaboratoryAngleEnergy::EnergyDistribution;
  using EnergyDistributionRange = RandomAccessAnyView< EnergyDistribution >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< EnergyDistribution >(
      viewmodule,
      "any_view< EnergyDistribution, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "AngularDistribution",
    "MF6 section - LAW=7 - the angular distributions associated to a given\n"
    "                      incident energy"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< EnergyDistribution >&& >(),
    python::arg( "energy" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "distributions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the incident energy\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    distributions    the secondary energy distributions"
  )
  .def_property_readonly(

    "NRM",
    &Component::NRM,
    "The number of interpolation regions for the cosines"
  )
  .def_property_readonly(

    "NMU",
    &Component::NMU,
    "The number of cosine values"
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

    "MU",
    [] ( const Component& self ) -> DoubleRange
       { return self.MU(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Component& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosines values"
  )
  .def_property_readonly(

    "energy_distributions",
    [] ( const Component& self ) -> EnergyDistributionRange
       { return self.energyDistributions(); },
    "The energy distributions"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law7
} // namespace mf6
