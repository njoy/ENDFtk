// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/458.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt458 {

void wrapPolynomialComponents( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 458 >;
  using Component = Section::PolynomialComponents;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "PolynomialComponents",
    "MF1 MT458 component - Polynomial evaluation for fission energy release\n"
    "                      components"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< std::array< double, 2 > >&& >(),
    python::arg( "efr" ), python::arg( "enp" ), python::arg( "end" ),
    python::arg( "egp" ), python::arg( "egd" ), python::arg( "eb" ),
    python::arg( "enu" ), python::arg( "er" ), python::arg( "et" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    efr     the kinetic energy of the fission fragments\n"
    "    enp     the kinetic energy of the prompt fission neutrons\n"
    "    end     the kinetic energy of the delayed fission neutrons\n"
    "    egp     the energy release by prompt gammas\n"
    "    egd     the energy release by delayed gammas\n"
    "    eb      the energy release by delayed betas\n"
    "    enu     the energy release by neutrinos\n"
    "    er      the total energy release minus neutrinos\n"
    "    et      the total energy release"
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

    "E",
    [] ( const Component& self ) -> DoubleRange3D
       { return self.E(); },
    "The energy release values and their uncertainties"
  )
  .def_property_readonly(

    "energy_release",
    [] ( const Component& self ) -> DoubleRange3D
       { return self.energyRelease(); },
    "The energy release values and their uncertainties"
  )
  .def_property_readonly(

    "EFR",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.EFR(); },
    "The kinetic energy of the fission fragments and its uncertainty"
  )
  .def_property_readonly(

    "fission_fragments",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.fissionFragments(); },
    "The kinetic energy of the fission fragments and its uncertainty"
  )
  .def_property_readonly(

    "ENP",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.ENP(); },
    "The kinetic energy of the prompt fission neutrons and its uncertainty"
  )
  .def_property_readonly(

    "prompt_neutrons",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.promptNeutrons(); },
    "The kinetic energy of the prompt fission neutrons and its uncertainty"
  )
  .def_property_readonly(

    "END",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.END(); },
    "The kinetic energy of the delayed fission neutrons and its uncertainty"
  )
  .def_property_readonly(

    "delayed_neutrons",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.delayedNeutrons(); },
    "The kinetic energy of the delayed fission neutrons and its uncertainty"
  )
  .def_property_readonly(

    "EGP",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.EGP(); },
    "The energy release by prompt gammas and its uncertainty"
  )
  .def_property_readonly(

    "prompt_gammas",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.promptGammas(); },
    "The energy release by prompt gammas and its uncertainty"
  )
  .def_property_readonly(

    "EGD",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.EGD(); },
    "The energy release by delayed gammas and its uncertainty"
  )
  .def_property_readonly(

    "delayed_gammas",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.delayedGammas(); },
    "The energy release by delayed gammas and its uncertainty"
  )
  .def_property_readonly(

    "EB",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.EB(); },
    "The energy release by delayed betas and its uncertainty"
  )
  .def_property_readonly(

    "delayed_betas",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.delayedBetas(); },
    "The energy release by delayed betas and its uncertainty"
  )
  .def_property_readonly(

    "ENU",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.ENU(); },
    "The energy release by neutrinos and its uncertainty"
  )
  .def_property_readonly(

    "neutrinos",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.neutrinos(); },
    "The energy release by neutrinos and its uncertainty"
  )
  .def_property_readonly(

    "ER",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.ER(); },
    "The the total energy release minus the neutrino energy and its uncertainty"
  )
  .def_property_readonly(

    "total_minus_neutrinos",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.totalMinusNeutrinos(); },
    "The the total energy release minus the neutrino energy and its uncertainty"
  )
  .def_property_readonly(

    "ET",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.ET(); },
    "The the total energy release and its uncertainty"
  )
  .def_property_readonly(

    "total",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.total(); },
    "The the total energy release and its uncertainty"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt458
} // namespace mf1
