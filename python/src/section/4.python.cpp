// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
void wrapIsotropic( python::module&, python::module& );
void wrapLegendreCoefficients( python::module&, python::module& );
void wrapTabulatedDistribution( python::module&, python::module& );
void wrapLegendreDistributions( python::module&, python::module& );
void wrapTabulatedDistributions( python::module&, python::module& );
void wrapMixedDistributions( python::module&, python::module& );

void wrapSection_4( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using Distributions = Section::Distributions;
  using Distribution = Section::Variant;
  using DistributionRange = BasicRandomAccessAnyView< Distribution >;

  // wrap components
  wrapIsotropic( module, viewmodule );
  wrapLegendreCoefficients( module, viewmodule );
  wrapTabulatedDistribution( module, viewmodule );
  wrapLegendreDistributions( module, viewmodule );
  wrapTabulatedDistributions( module, viewmodule );
  wrapMixedDistributions( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< Distribution >(
      viewmodule,
      "any_view< variant< LegendreCoefficients&, TabulatedDistribution& >, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF4 section - angular distributions of secondary particles"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, int, Distributions&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lct" ), python::arg( "distributions" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self             the section\n"
    "    mt               the MT number\n"
    "    zaid             the ZA  identifier\n"
    "    awr              the atomic mass ratio\n"
    "    lct              the reference frame\n"
    "    distributions    the distributions"
  )
  .def_property_readonly(

    "LCT",
    &Section::LCT,
    "The reference frame"
  )
  .def_property_readonly(

    "reference_frame",
    &Section::referenceFrame,
    "The reference frame"
  )
  .def_property_readonly(

    "LTT",
    &Section::LTT,
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    &Section::LAW,
    "The distribution law"
  )
  .def_property_readonly(

    "LI",
    &Section::LI,
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "isotropic_distributions",
    &Section::isotropicDistributions,
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "distributions",
    &Section::distributions,
    "The partial distributions defined in this section"
  )
  .def_property_readonly(

    "NE",
    &Section::NE,
    "The number of incident energy values for which angular distributions\n"
    "are given"
  )
  .def_property_readonly(

    "NR",
    &Section::NR,
    "The number of interpolation ranges"
  )
  .def_property_readonly(

    "interpolants",
    &Section::interpolants,
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "boundaries",
    &Section::boundaries,
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "incident_energies",
    &Section::incidentEnergies,
    "The incident energies"
  )
  .def_property_readonly(

    "angular_distributions",
    &Section::angularDistributions,
    "The angular distributions (one for each incident energy)"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
