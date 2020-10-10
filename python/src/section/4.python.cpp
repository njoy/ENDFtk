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
void wrapIsotropic( python::module& );
void wrapLegendreCoefficients( python::module& );
void wrapTabulatedDistribution( python::module& );

void wrapSection_4( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using Distributions = njoy::ENDFtk::section::Type< 4 >::Distributions;

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF3 section - reaction cross sections"
  );

  // wrap components
  wrapIsotropic( module );
  wrapLegendreCoefficients( module );
  wrapTabulatedDistribution( module );

  // wrap the section
  section
//  .def(
//
//    python::init< int, double, double, int, Distributions&& >,
//    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
//    python::arg( "lct" ), python::arg( "distributions" ),
//    "Initialise the section\n\n"
//    "Arguments:\n"
//    "    self             the section\n"
//    "    mt               the MT number\n"
//    "    zaid             the ZA  identifier\n"
//    "    awr              the atomic mass ratio\n"
//    "    lct              the reference frameo\n"
//    "    distributions    the distributionso"
//  )
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

    "isotropic_angular_distributions",
    &Section::isotropicAngularDistributions,
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "distributions",
    &Section::distributions,
    "The partial distributions defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
