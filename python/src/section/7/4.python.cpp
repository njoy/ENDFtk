// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

  // declarations - components
  void wrapEffectiveTemperature( python::module& );
  void wrapAnalyticalFunctions( python::module& );
  void wrapTabulated( python::module& );
  void wrapScatteringFunction( python::module& );
  void wrapScatteringLawConstants( python::module& );

}

void wrapSection_7_4( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 4 >;
  using ScatteringLaw = njoy::ENDFtk::section::Type< 7, 4 >::ScatteringLaw;
  using EffectiveTemperature = njoy::ENDFtk::section::Type< 7, 4 >::EffectiveTemperature;
  using ScatteringLawConstants = njoy::ENDFtk::section::Type< 7, 4 >::ScatteringLawConstants;
  using EffectiveTemperatureRange = RandomAccessAnyView< std::optional< EffectiveTemperature > >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< std::optional< EffectiveTemperature > >(
      module,
      "any_view< std::optional< EffectiveTemperature >, random_access >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT4",
    "MT4 - incoherent inelastic scattering"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF7 MT4 section - incoherent inelastic scattering"
  );

  // wrap components
  mf7::wrapScatteringLawConstants( submodule );
  mf7::wrapAnalyticalFunctions( submodule );
  mf7::wrapTabulated( submodule );
  mf7::wrapScatteringFunction( submodule );
  mf7::wrapEffectiveTemperature( submodule );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr, int lat, int lasym,
                       ScatteringLawConstants constants,
                       ScatteringLaw law,
                       EffectiveTemperature principal,
                       std::vector< std::optional< EffectiveTemperature > > secondaries )
                     { return Section( zaid, awr, lat, lasym,
                                       std::move( constants ),
                                       std::move( law ),
                                       std::move( principal ),
                                       std::move( secondaries ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lat" ),
    python::arg( "lasym" ), python::arg( "constants" ), python::arg( "law" ),
    python::arg( "principal" ), python::arg( "secondaries" ) =
        std::vector< std::optional< EffectiveTemperature > >{},
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    zaid           the ZA value of the material\n"
    "    awr            the atomic weight ratio\n"
    "    lat            the temperature flag for alpha and beta grid\n"
    "    lasym          the S(a,b) symmetry flag\n"
    "    constants      the thermal scattering law constants\n"
    "    law            the thermal scattering law\n"
    "    principal      the effective temperature of the\n"
    "                   principal scatterer\n"
    "    secondaries    the effective temperature of the\n"
    "                   secondary scatterers (if required)"
  )
  .def_property_readonly(

    "LAT",
    &Section::LAT,
    "The LAT flag (temperature flag for alpha and beta grid)"
  )
  .def_property_readonly(

    "temperature_option",
    &Section::temperatureOption,
    "The LAT flag (temperature flag for alpha and beta grid)"
  )
  .def_property_readonly(

    "LASYM",
    &Section::LASYM,
    "The LASYM flag (S(alpha,beta) is symmetric or not)"
  )
  .def_property_readonly(

    "symmetry_option",
    &Section::symmetryOption,
    "The LASYM flag (S(alpha,beta) is symmetric or not)"
  )
  .def_property_readonly(

    "constants",
    &Section::constants,
    "The thermal scattering law constants for the principal and and secondary\n"
    "scatterers (if any)"
  )
  .def_property_readonly(

    "principal_effective_temperature",
    &Section::principalEffectiveTemperature,
    "The effective temperature for the principal scatterer"
  )
  .def_property_readonly(

    "secondary_effective_temperatures",
    [] ( const Section& self ) -> EffectiveTemperatureRange
       { return self.secondaryEffectiveTemperatures(); },
    "The effective temperatures for the secondary scatterers (if any are\n"
    "defined)"
  )
  .def_property_readonly(

    "scattering_law",
    &Section::scatteringLaw,
    "The LTHR flag (coherent or incoherent elastic scattering)"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
