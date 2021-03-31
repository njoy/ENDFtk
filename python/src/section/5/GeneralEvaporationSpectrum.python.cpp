// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGeneralEvaporationSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 5 >;
  using Component = Section::GeneralEvaporationSpectrum;
  using EffectiveTemperature = Section::EffectiveTemperature;
  using DistributionFunction = Section::DistributionFunction;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "GeneralEvaporationSpectrum",
    "MF5 section - the general evaporation spectrum (LF=5)"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( EffectiveTemperature temperature,
                       DistributionFunction distribution )
                     { return Component( std::move( temperature ),
                                         std::move( distribution ) ); } ),
    python::arg( "temperature" ), python::arg( "distribution" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    temperature     the effective temperature\n"
    "    distribution    the distribution function g(x)"
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

    "theta",
    &Component::theta,
    "The effective temperature"
  )
  .def_property_readonly(

    "effective_temperature",
    &Component::effectiveTemperature,
    "The effective temperature"
  )
  .def_property_readonly(

    "g",
    &Component::g,
    "The distribution function g(x)"
  )
  .def_property_readonly(

    "distribution_function",
    &Component::distributionFunction,
    "The distribution function g(x)"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
