// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMixedDistributions( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using Component = Section::MixedDistributions;
  using LegendreCoefficients = Section::LegendreCoefficients;
  using TabulatedDistribution = Section::TabulatedDistribution;
  using LegendreDistributions = Section::LegendreDistributions;
  using TabulatedDistributions = Section::TabulatedDistributions;
  using Distribution = Section::Variant;
  using DistributionRange = BasicRandomAccessAnyView< Distribution >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "MixedDistributions",
    "MF4 section - the angular distributions are mixed (Legendre coefficients\n"
    "              and tabulated distributions)"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( LegendreDistributions legendre,
                       TabulatedDistributions tabulated )
                     { return Component( std::move( legendre ),
                                         std::move( tabulated ) ); } ),
    python::arg( "legendre" ), python::arg( "tabulated" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    legendre         the legendre distributions\n"
    "    tabulated        the tabulated distributions"
  )
  .def_property_readonly(

    "LI",
    [] ( const Component& self ) { return self.LI(); },
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "isotropic_angular_distributions",
    [] ( const Component& self ) { return self.isotropicAngularDistributions(); },
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "LTT",
    [] ( const Component& self ) { return self.LTT(); },
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution law"
  )
  .def_property_readonly(

    "legendre",
    &Component::legendre,
    "The Legendre distributions"
  )
  .def_property_readonly(

    "tabulated",
    &Component::tabulated,
    "The tabulated distributions"
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

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
