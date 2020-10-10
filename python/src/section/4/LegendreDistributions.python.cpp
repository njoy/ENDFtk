// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 4 >::LegendreDistributions;
  using Distribution = njoy::ENDFtk::section::Type< 4 >::LegendreCoefficients;
  using DistributionRange = RandomAccessAnyView< Distribution >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LegendreDistributions",
    "MF4 section - angular distributions as a function of incident energy\n"
    "              using Legendre coefficients (LTT=1)"
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
    "    distributions    the sequence of angular distributions"
  )
  .def_property_readonly(

    "LTT",
    &Component::LTT,
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution law"
  )
  .def_property_readonly(

    "NE",
    [] ( const Component& self ) { return self.NE(); },
    "The number of incident energy values for which angular distributions\n"
    "are given"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energies"
  )
  .def_property_readonly(

    "angular_distributions",
    [] ( const Component& self ) -> DistributionRange
       { return self.angularDistributions(); },
    "The angular distributions (one for each incident energy)"
  );

  // add standard tab2 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
