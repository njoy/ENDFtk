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

void wrapLaboratoryAngleEnergy( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::LaboratoryAngleEnergy;
  using AngularDistribution = Section::LaboratoryAngleEnergy::AngularDistribution;
  using AngularDistributionRange = RandomAccessAnyView< AngularDistribution >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< AngularDistribution >(
      viewmodule,
      "any_view< AngularDistribution, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "LaboratoryAngleEnergy",
    "MF6 section - LAW=7 - distributions are given in the E,mu,E' ordering"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< AngularDistribution >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "distributions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    distributions    the secondary energy distributions"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
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

    "angular_distributions",
    [] ( const Component& self ) -> AngularDistributionRange
       { return self.angularDistributions(); },
    "The angular distributions"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf6
