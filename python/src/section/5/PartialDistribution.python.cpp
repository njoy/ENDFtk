// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPartialDistribution( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 5 >;
  using Component = Section::PartialDistribution;
  using Probability = Section::Probability;
  using Distribution = Section::Distribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "PartialDistribution",
    "MF5 section - a distribution subsection of an MF5 section"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( Probability probability, Distribution distribution )
                     { return Component( std::move( probability ),
                                         std::move( distribution ) ); } ),
    python::arg( "probability" ), python::arg( "spectrum" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    probability    the probability\n"
    "    spectrum       the spectrum"
  )
  .def_property_readonly(

    "U",
    &Component::U,
    "The energy limit constant"
  )
  .def_property_readonly(

    "energy_limit_constant",
    &Component::energyLimitConstant,
    "The energy limit constant"
  )
  .def_property_readonly(

    "probability",
    &Component::probability,
    "The probability"
  )
  .def_property_readonly(

    "distribution",
    &Component::distribution,
    "The distribution"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
