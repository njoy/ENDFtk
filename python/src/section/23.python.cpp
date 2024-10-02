// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/23.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_23( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 23 >;

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF23 section - smooth photon interaction cross sections"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double, double, double,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "epe" ), python::arg( "efl" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    mt             the MT number\n"
    "    zaid           the ZA  identifier\n"
    "    awr            the atomic mass ratio\n"
    "    epe            the subshell binding energy\n"
    "    efl            the fluorescence yield\n"
    "    boundaries     the interpolation range boundaries\n"
    "    interpolants   the interpolation types for each range\n"
    "    energies       the energy values\n"
    "    xs             the cross section values"
  )
  .def_property_readonly(

    "EPE",
    &Section::EPE,
    "The subshell binding energy"
  )
  .def_property_readonly(

    "subshell_binding_energy",
    &Section::subshellBindingEnergy,
    "The subshell binding energy"
  )
  .def_property_readonly(

    "EFL",
    &Section::EFL,
    "The fluorescence yield (eV/photoionisation)"
  )
  .def_property_readonly(

    "fluorescence_yield",
    &Section::fluorescenceYield,
    "The fluorescence yield (eV/photoionisation)"
  )
  .def_property_readonly(

    "energies",
    [] ( const Section& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Section& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Section >( section );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
