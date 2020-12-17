// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/2.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapCoherentElastic( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 7, 2 >::CoherentElastic;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CoherentElastic",
    "MF7 MT2 section - coherent elastic scattering"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< long >&&,
                  std::vector< double >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "temperatures" ), python::arg( "li" ),
    python::arg( "energies" ), python::arg( "s" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries for S(E)\n"
    "    interpolants    the interpolation types for each range\n"
    "    temperatures    the temperatures (NT values)\n"
    "    li              the temperature interpolation flags (NT-1 values)\n"
    "    energies        the energy values (NP values)\n"
    "    s               the thermal scattering values (NT arrays of NP values)"
  )
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "temperature" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "s" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    temperature     the temperature\n"
    "    boundaries      the interpolation range boundaries for S(E)\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values (NP values)\n"
    "    s               the thermal scattering values (NP values)"
  )
  .def_property_readonly(

    "LTHR",
    [] ( const Component& self )
       { return self.LTHR(); },
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
  )
  .def_property_readonly(

    "elastic_scattering_type",
    &Component::elasticScatteringType,
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
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

    "number_bragg_edges",
    &Component::numberBraggEdges,
    "The number of Bragg edges, equal to the number of energy values"
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

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
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
