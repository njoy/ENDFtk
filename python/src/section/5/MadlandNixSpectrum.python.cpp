// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMadlandNixSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 5 >;
  using Component = Section::MadlandNixSpectrum;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "MadlandNixSpectrum",
    "MF5 section - the Madland Nix fission neutron spectrum (LF=12)"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "efl" ), python::arg( "efh" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "temperatures" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    efl             the light fission fragment kinetic energy\n"
    "    efh             the heavy fission fragment kinetic energy\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    temperatures    the maximum temperature values\n"
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

    "EFL",
    &Component::EFL,
    "The average kinetic energy of the average light fission fragment"
  )
  .def_property_readonly(

    "light_fragment_energy",
    &Component::lightFragmentEnergy,
    "The average kinetic energy of the average light fission fragment"
  )
  .def_property_readonly(

    "EFH",
    &Component::EFH,
    "The average kinetic energy of the average heavy fission fragment"
  )
  .def_property_readonly(

    "heavy_fragment_energy",
    &Component::heavyFragmentEnergy,
    "The average kinetic energy of the average heavy fission fragment"
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

    "TM",
    [] ( const Component& self ) -> DoubleRange
       { return self.TM(); },
    "The maximum temperature parameter values"
  )
  .def_property_readonly(

    "maximum_temperature_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.maximumTemperatureValues(); },
    "The maximum temperature parameter values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
