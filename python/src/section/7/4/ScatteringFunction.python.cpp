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

void wrapScatteringFunction( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 7, 4 >::Tabulated::ScatteringFunction;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ScatteringFunction",
    "MF7 MT4 section - S(alpha,beta,T) data for a fixed value of beta"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< long >&&,
                  std::vector< long >&&,
                  std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "temperature" ),  python::arg( "beta" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "alphas" ), python::arg( "sab" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    temperature     the temperature\n"
    "    beta            the beta value for which data will be given\n"
    "    boundaries      the interpolation range boundaries for S(a,beta)\n"
    "    interpolants    the interpolation types for each range\n"
    "    alphas          the alpha values (NA values)\n"
    "    sab             the thermal scattering values (NA values)"
  )
  .def(

    python::init< double,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< long >&&,
                  std::vector< double >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "beta" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "temperatures" ),
    python::arg( "li" ), python::arg( "alphas" ), python::arg( "sab" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    beta            the beta value for which data will be given\n"
    "    boundaries      the interpolation range boundaries for S(a,beta)\n"
    "    interpolants    the interpolation types for each range\n"
    "    temperatures    the temperatures (NT values)\n"
    "    li              the temperature interpolation flags (NT-1 values)\n"
    "    alphas          the alpha values (NA values)\n"
    "    sab             the thermal scattering values (NT arrays of NA values)"
  )
  .def_property_readonly(

    "B",
    &Component::B,
    "The current beta value"
  )
  .def_property_readonly(

    "beta",
    &Component::beta,
    "The current beta value"
  )
  .def_property_readonly(

    "LT",
    &Component::LT,
    "The LT flag indicating the temperature dependence (equal to NT - 1)"
  )
  .def_property_readonly(

    "temperature_dependence_flag",
    &Component::temperatureDependenceFlag,
    "The LT flag indicating the temperature dependence (equal to NT - 1)"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "The number of temperatures"
  )
  .def_property_readonly(

    "number_temperatures",
    &Component::numberTemperatures,
    "The number of temperatures"
  )
  .def_property_readonly(

    "NA",
    &Component::NA,
    "The number of alpha values"
  )
  .def_property_readonly(

    "number_alphas",
    &Component::numberAlphas,
    "The number of alpha values"
  )
  .def_property_readonly(

    "T",
    [] ( const Component& self ) -> DoubleRange
       { return self.T(); },
    "The temperature values"
  )
  .def_property_readonly(

    "temperatures",
    [] ( const Component& self ) -> DoubleRange
       { return self.temperatures(); },
    "The temperature values"
  )
  .def_property_readonly(

    "A",
    [] ( const Component& self ) -> DoubleRange
       { return self.A(); },
    "The alpha grid"
  )
  .def_property_readonly(

    "alphas",
    [] ( const Component& self ) -> DoubleRange
       { return self.alphas(); },
    "The alpha grid"
  )
  .def_property_readonly(

    "LI",
    [] ( const Component& self ) -> IntRange
       { return self.LI(); },
    "The temperature interpolation flags (LT values will be given)"
  )
  .def_property_readonly(

    "temperature_interpolants",
    [] ( const Component& self ) -> IntRange
       { return self.temperatureInterpolants(); },
    "The temperature interpolation flags (LT values will be given)"
  )
  .def_property_readonly(

    "S",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.S(); },
    "The thermal scattering law values as an array, one for each temperature"
  )
  .def_property_readonly(

    "thermal_scattering_values",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.thermalScatteringValues(); },
    "The thermal scattering law values as an array, one for each temperature"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
