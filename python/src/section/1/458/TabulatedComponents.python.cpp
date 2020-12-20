// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/458.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt458 {

void wrapTabulatedComponents( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 458 >;
  using Component = Section::TabulatedComponents;
  using ThermalPointComponents = Section::ThermalPointComponents;
  using EnergyReleaseComponent = Section::EnergyReleaseComponent;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedComponents",
    "MF1 MT458 component - tabulated evaluation for fission energy release \n"
    "                      components"
  );

  // wrap the component
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( ThermalPointComponents thermal,
                       std::vector< EnergyReleaseComponent >&& tables )
                     { return Component( std::move( thermal ),
                                         std::move( tables ) ); } ),
    python::arg( "thermal" ), python::arg( "tables" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    thermal    the thermal point evaluation of the energy release\n"
    "    tables     the tabulated components"
  )
  .def_property_readonly(

    "LFC",
    [] ( const Component& self ) { return self.LFC(); },
    "The tabulated energy release flag"
  )
  .def_property_readonly(

    "tabulated_energy_release",
    &Component::tabulatedEnergyRelease,
    "The tabulated energy release flag"
  )
  .def_property_readonly(

    "NPLY",
    [] ( const Component& self ) { return self.NPLY(); },
    "The polynomial expansion order"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The polynomial expansion order"
  )
  .def_property_readonly(

    "NFC",
    [] ( const Component& self ) { return self.NFC(); },
    "The number of tabulated energy release components"
  )
  .def_property_readonly(

    "number_tabulated_components",
    &Component::numberTabulatedComponents,
    "The number of tabulated energy release components"
  )
  .def_property_readonly(

    "thermal_point_values",
    &Component::thermalPointValues,
    "The thermal point values"
  )
  .def_property_readonly(

    "tabulated_EFR",
    &Component::tabulatedEFR,
    "The tabulated kinetic energy of the fission fragments"
  )
  .def_property_readonly(

    "tabulated_fission_fragments",
    &Component::tabulatedFissionFragments,
    "The tabulated kinetic energy of the fission fragments"
  )
  .def_property_readonly(

    "tabulated_ENP",
    &Component::tabulatedENP,
    "The tabulated kinetic energy of the prompt fission neutrons"
  )
  .def_property_readonly(

    "tabulated_prompt_neutrons",
    &Component::tabulatedPromptNeutrons,
    "The tabulated kinetic energy of the prompt fission neutrons"
  )
  .def_property_readonly(

    "tabulated_END",
    &Component::tabulatedEND,
    "The tabulated kinetic energy of the delayed fission neutrons"
  )
  .def_property_readonly(

    "tabulated_delayed_neutrons",
    &Component::tabulatedDelayedNeutrons,
    "The tabulated kinetic energy of the delayed fission neutrons"
  )
  .def_property_readonly(

    "tabulated_EGP",
    &Component::tabulatedEGP,
    "The tabulated energy release by prompt gammas"
  )
  .def_property_readonly(

    "tabulated_prompt_gammas",
    &Component::tabulatedPromptGammas,
    "The tabulated energy release by prompt gammas"
  )
  .def_property_readonly(

    "tabulated_EGD",
    &Component::tabulatedEGD,
    "The tabulated energy release by delayed gammas"
  )
  .def_property_readonly(

    "tabulated_delayed_gammas",
    &Component::tabulatedDelayedGammas,
    "The tabulated energy release by delayed gammas"
  )
  .def_property_readonly(

    "tabulated_EB",
    &Component::tabulatedEB,
    "The tabulated energy release by delayed betas"
  )
  .def_property_readonly(

    "tabulated_delayed_betas",
    &Component::tabulatedDelayedBetas,
    "The tabulated energy release by delayed betas"
  )
  .def_property_readonly(

    "tabulated_ENU",
    &Component::tabulatedENU,
    "The tabulated energy release by neutrinos"
  )
  .def_property_readonly(

    "tabulated_neutrinos",
    &Component::tabulatedNeutrinos,
    "The tabulated energy release by neutrinos"
  )
  .def_property_readonly(

    "tabulated_ER",
    &Component::tabulatedER,
    "The tabulated total energy release minus the neutrino energy"
  )
  .def_property_readonly(

    "tabulated_total_minus_neutrinos",
    &Component::tabulatedTotalMinusNeutrinos,
    "The tabulated total energy release minus the neutrino energy"
  )
  .def_property_readonly(

    "tabulated_ET",
    &Component::tabulatedET,
    "The tabulated total energy release"
  )
  .def_property_readonly(

    "tabulated_total",
    &Component::tabulatedTotal,
    "The the total energy release"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "component" ),
    "Copy the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    component    the component to be copied"
  )
  .def_property_readonly(

    "NC",
    [] ( const Component& self ) { return self.NC(); },
    "The number of lines in this component"
  )
  .def(

    "to_string",
    [] ( const Component& self, int mat, int mf, int mt ) -> std::string
       { return print( self, mat, mf, mt ); },
    python::arg( "mat" ), python::arg( "mf" ), python::arg( "mt" ),
    "Return the string representation of the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used\n"
    "    mt      the MT number to be used"
  );

  // no standard definitions - read constructor needs number of tables
}

} // namespace mt458
} // namespace mf1
