// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/26.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf26 {

void wrapContinuumEnergyAngle( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;
  using Component = Section::ContinuumEnergyAngle;
  using LegendreCoefficients = Section::ContinuumEnergyAngle::LegendreCoefficients;
  using LegendreCoefficientsRange = RandomAccessAnyView< LegendreCoefficients >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< LegendreCoefficients >(
      viewmodule,
      "any_view< law1::LegendreCoefficients >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ContinuumEnergyAngle",
    "MF26 section - LAW=1 - continuum energy-angle data for secondary particles"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< LegendreCoefficients >&& >(),
    python::arg( "lep" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "distributions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    lep              the secondary energy interpolation scheme\n"
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

    "LEP",
    &Component::LEP,
    "The interpolation scheme for secondary energies"
  )
  .def_property_readonly(

    "interpolation_scheme",
    &Component::interpolationScheme,
    "The interpolation scheme for secondary energies"
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
    [] ( const Component& self ) -> LegendreCoefficientsRange
       { return self.distributions(); },
    "The distributions"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf26
